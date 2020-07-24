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
import com.nabiki.ctp4j.md.CThostFtdcMdApi;
import com.nabiki.ctp4j.md.CThostFtdcMdSpi;
import com.nabiki.iop.x.OP;
import com.nabiki.iop.x.SystemStream;

import java.io.File;
import java.util.concurrent.CountDownLatch;

public class MdApiTest {
    static {
        try {
            SystemStream.setErr(new File("err.txt"));
            SystemStream.setOut(new File("out.txt"));
        } catch (Throwable th) {
            th.printStackTrace();
        }
    }

    class SpiTest extends CThostFtdcMdSpi {
        public SpiTest() {
        }

        @Override
        public void OnFrontConnected() {
            System.out.println("OnFrontConnected");
        }

        @Override
        public void OnFrontDisconnected(int reason) {
            System.out.println("OnFrontDisconnected: " + reason);
        }

        @Override
        public void OnRspError(
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspError");
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspUserLogin(
                CThostFtdcRspUserLoginField rspUserLogin,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspUserLogin");
            System.out.println(OP.toJson(rspUserLogin));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspUserLogout(
                CThostFtdcUserLogoutField userLogout,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspUserLogout");
            System.out.println(OP.toJson(userLogout));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspSubMarketData(
                CThostFtdcSpecificInstrumentField specificInstrument,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspSubMarketData");
            System.out.println(OP.toJson(specificInstrument));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspUnSubMarketData(
                CThostFtdcSpecificInstrumentField specificInstrument,
                CThostFtdcRspInfoField rspInfo,
                int nRequestID,
                boolean isLast) {
            System.out.println("OnRspUnSubMarketData");
            System.out.println(OP.toJson(specificInstrument));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + nRequestID);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRtnDepthMarketData(
                CThostFtdcDepthMarketDataField depthMarketData) {
            System.out.println("OnRtnDepthMarketData");
            System.out.println(OP.toJson(depthMarketData));
        }
    }

    void sleep(int millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public void basic() {
        IOPConnector.executablePath = "C:\\Workspace\\ctp4j-family\\cpp\\x64\\Debug\\ctp4j-gate.exe";

        var api = CThostFtdcMdApi.CreateFtdcMdApi("", false, false);
        api.RegisterSpi(new SpiTest());
        api.RegisterFront("tcp://180.168.146.187:10111");
        api.Init();

        int id = 0, opCode = -1;

        // Sleep.
        sleep(1000);

        var login = new CThostFtdcReqUserLoginField();
        login.BrokerID = "9999";
        login.UserID = "144287";
        login.Password = "chb_1987_1013";
        api.ReqUserLogin(login, ++id);

        sleep(1000);

        // Subscribe.
        var sub = new String[] {"au2012", "ag2012"};
        api.SubscribeMarketData(sub, 2);

        // Un-subscribe.
        sleep(15 * 1000);
        api.UnSubscribeMarketData(sub, 2);
    }

    public static void main(String[] args) {
        new MdApiTest().basic();
        try {
            new CountDownLatch(1).await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
