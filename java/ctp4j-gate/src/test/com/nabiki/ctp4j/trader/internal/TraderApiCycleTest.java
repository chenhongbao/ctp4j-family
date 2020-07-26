/*
 * Copyright (c) 2020 Hongbao Chen <chenhongbao@outlook.com>
 *
 * Licensed under the  GNU Affero General Public License v3.0 and you may not use
 * this file except in compliance with the  License. You may obtain a copy of the
 * License at
 *
 *                    https://www.gnu.org/licenses/agpl-3.0.txt
 *
 * Permission is hereby  granted, free of charge, to any  person obtaining a copy
 * of this software and associated  documentation files (the "Software"), to deal
 * in the Software  without restriction, including without  limitation the rights
 * to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
 * copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
 * IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
 * FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
 * AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
 * LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.nabiki.ctp4j.trader.internal;

import com.nabiki.ctp4j.internal.IOPConnector;
import com.nabiki.ctp4j.jni.struct.*;
import com.nabiki.ctp4j.trader.CThostFtdcTraderApi;
import com.nabiki.ctp4j.trader.CThostFtdcTraderSpi;
import com.nabiki.iop.x.OP;
import com.nabiki.iop.x.SystemStream;
import org.junit.Test;

import java.io.File;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

public class TraderApiCycleTest {
    enum RspState {
        OnFrontConnected,
        OnFrontDisconnected,
        OnRspAuthenticate,
        OnRspSettlementInfoConfirm,
        OnRspUserLogin,
        OnRspUserLogout,
        OnRspError
    }

    static {
        try {
            SystemStream.setErr(new File("err.txt"));
            SystemStream.setOut(new File("out.txt"));
        } catch (Throwable th) {
            th.printStackTrace();
        }
    }

    private int currentRequestID = 0;
    private RspState rspState = RspState.OnFrontDisconnected;
    private CThostFtdcTraderApi api;

    class CycleTestSpi extends CThostFtdcTraderSpi {
        @Override
        public void OnFrontConnected() {
            System.out.println("OnFrontConnected");
            rspState = RspState.OnFrontConnected;
        }

        @Override
        public void OnFrontDisconnected(int reason) {
            assertEquals(0, reason);
            System.out.println("OnFrontDisconnected");
            rspState = RspState.OnFrontDisconnected;
        }

        @Override
        public void OnRspAuthenticate(
                CThostFtdcRspAuthenticateField rspAuthenticateField,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            assertEquals(RspState.OnFrontConnected, rspState);
            assertEquals(0, rspInfo.ErrorID);
            assertEquals(requestId, currentRequestID);
            rspState = RspState.OnRspAuthenticate;
        }

        @Override
        public void OnRspSettlementInfoConfirm(
                CThostFtdcSettlementInfoConfirmField settlementInfoConfirm,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            assertEquals(RspState.OnRspUserLogin, rspState);
            assertEquals(0, rspInfo.ErrorID);
            assertEquals(requestId, currentRequestID);
            rspState = RspState.OnRspSettlementInfoConfirm;
        }

        @Override
        public void OnRspUserLogin(
                CThostFtdcRspUserLoginField rspUserLogin,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            assertEquals(RspState.OnRspAuthenticate, rspState);
            assertEquals(0, rspInfo.ErrorID);
            assertEquals(requestId, currentRequestID);
            rspState = RspState.OnRspUserLogin;
        }

        @Override
        public void OnRspUserLogout(
                CThostFtdcUserLogoutField userLogout,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            assertEquals(RspState.OnRspSettlementInfoConfirm, rspState);
            assertEquals(0, rspInfo.ErrorID);
            assertEquals(requestId, currentRequestID);
            rspState = RspState.OnRspUserLogout;
        }

        @Override
        public void OnRspError(
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            assertNotEquals(0, rspInfo.ErrorID);
            assertEquals(requestId, currentRequestID);
            System.out.println(OP.toJson(rspInfo));
        }
    }

    void sleep(int millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void login_out() {
        var auth = new CThostFtdcReqAuthenticateField();
        auth.UserProductInfo = "ctp4j-test";
        auth.UserID = "144287";
        auth.BrokerID = "9999";
        auth.AppID = "3430491819";
        auth.AuthCode = "0000000000000000";
        api.ReqAuthenticate(auth, ++currentRequestID);

        sleep(1000);

        var login = new CThostFtdcReqUserLoginField();
        login.BrokerID = "9999";
        login.UserID = "144287";
        login.Password = "chb_1987_1013";
        api.ReqUserLogin(login, ++currentRequestID);

        sleep(1000);

        var confirm = new CThostFtdcSettlementInfoConfirmField();
        confirm.CurrencyID = "CNY";
        confirm.BrokerID = "9999";
        confirm.AccountID = confirm.InvestorID = "144287";
        api.ReqSettlementInfoConfirm(confirm, ++currentRequestID);

        sleep(1000);

        var logout = new CThostFtdcUserLogoutField();
        logout.UserID = "144287";
        logout.BrokerID = "9999";
        api.ReqUserLogout(logout, ++currentRequestID);

        sleep(1000);
    }

    private void cycle(int count) {
        IOPConnector.executablePath = "C:\\Workspace\\ctp4j-family\\cpp\\x64\\Debug\\ctp4j-gate.exe";

        api = CThostFtdcTraderApi.CreateFtdcTraderApi("");
        api.RegisterSpi(new CycleTestSpi());
        api.RegisterFront("tcp://180.168.146.187:10101");
        api.SubscribePublicTopic(0);
        api.SubscribePrivateTopic(0);

        // Start.
        api.Init();

        // Test some rounds.
        while (--count > 0)
            login_out();

        // Stop.
        api.Release();
    }

    private void init_release(int count) {
        IOPConnector.executablePath = "C:\\Workspace\\ctp4j-family\\cpp\\x64\\Debug\\ctp4j-gate.exe";

        api = CThostFtdcTraderApi.CreateFtdcTraderApi("");
        api.RegisterSpi(new CycleTestSpi());
        api.RegisterFront("tcp://180.168.146.187:10101");
        api.SubscribePublicTopic(0);
        api.SubscribePrivateTopic(0);

        while (--count > 0)
            try {
                // Start.
                api.Init();

                // Release.
                sleep(1000);
                api.Release();
            } catch (Throwable th) {
                th.printStackTrace();
            }
    }

    @Test
    public void basic() {
        init_release(1000);
    }
}