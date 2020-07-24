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
import com.nabiki.ctp4j.jni.flag.*;
import com.nabiki.ctp4j.jni.struct.*;
import com.nabiki.ctp4j.trader.CThostFtdcTraderApi;
import com.nabiki.ctp4j.trader.CThostFtdcTraderSpi;
import com.nabiki.iop.x.OP;
import com.nabiki.iop.x.SystemStream;

import java.io.File;
import java.util.concurrent.CountDownLatch;


public class TraderApiTest {

    static {
        try {
            SystemStream.setErr(new File("err.txt"));
            SystemStream.setOut(new File("out.txt"));
        } catch (Throwable th) {
            th.printStackTrace();
        }
    }

    class SpiTest extends CThostFtdcTraderSpi {
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
        public void OnErrRtnOrderAction(
                CThostFtdcOrderActionField orderAction,
                CThostFtdcRspInfoField rspInfo) {
            System.out.println("OnErrRtnOrderAction");
            System.out.println(OP.toJson(orderAction));
            System.out.println(OP.toJson(rspInfo));
        }

        @Override
        public void OnErrRtnOrderInsert(
                CThostFtdcInputOrderField inputOrder,
                CThostFtdcRspInfoField rspInfo) {
            System.out.println("OnErrRtnOrderInsert");
            System.out.println(OP.toJson(inputOrder));
            System.out.println(OP.toJson(rspInfo));
        }

        @Override
        public void OnRspAuthenticate(
                CThostFtdcRspAuthenticateField rspAuthenticateField,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspAuthenticate");
            System.out.println(OP.toJson(rspAuthenticateField));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
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
        public void OnRspOrderAction(
                CThostFtdcInputOrderActionField inputOrderAction,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspOrderAction");
            System.out.println(OP.toJson(inputOrderAction));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspOrderInsert(
                CThostFtdcInputOrderField inputOrder,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspOrderInsert");
            System.out.println(OP.toJson(inputOrder));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspQryInstrument(
                CThostFtdcInstrumentField instrument,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspQryInstrument");
            System.out.println(OP.toJson(instrument));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspQryInstrumentCommissionRate(
                CThostFtdcInstrumentCommissionRateField instrumentCommissionRate,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspQryInstrumentCommissionRate");
            System.out.println(OP.toJson(instrumentCommissionRate));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspQryInstrumentMarginRate(
                CThostFtdcInstrumentMarginRateField instrumentMarginRate,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspQryInstrumentMarginRate");
            System.out.println(OP.toJson(instrumentMarginRate));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspQryInvestorPositionDetail(
                CThostFtdcInvestorPositionDetailField investorPositionDetail,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspQryInvestorPositionDetail");
            System.out.println(OP.toJson(investorPositionDetail));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspQryTradingAccount(
                CThostFtdcTradingAccountField tradingAccount,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspQryTradingAccount");
            System.out.println(OP.toJson(tradingAccount));
            System.out.println(OP.toJson(rspInfo));
            System.out.println("requestID: " + requestId);
            System.out.println("isLast: " + isLast);
        }

        @Override
        public void OnRspSettlementInfoConfirm(
                CThostFtdcSettlementInfoConfirmField settlementInfoConfirm,
                CThostFtdcRspInfoField rspInfo,
                int requestId,
                boolean isLast) {
            System.out.println("OnRspSettlementInfoConfirm");
            System.out.println(OP.toJson(settlementInfoConfirm));
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
        public void OnRtnOrder(CThostFtdcOrderField order) {
            System.out.println("OnRtnOrder");
            System.out.println(OP.toJson(order));
            if (order.OrderStatus == TThostFtdcOrderStatusType.NO_TRADE_QUEUEING)
                rtnOrder = order;
        }

        @Override
        public void OnRtnTrade(CThostFtdcTradeField trade) {
            System.out.println("OnRtnTrade");
            System.out.println(OP.toJson(trade));
        }
    }

    void sleep(int millis) {
        try {
            Thread.sleep(millis);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private CThostFtdcOrderField rtnOrder;

    public void basic() {
        IOPConnector.executablePath = "C:\\Workspace\\ctp4j-family\\cpp\\x64\\Debug\\ctp4j-gate.exe";

        var api = CThostFtdcTraderApi.CreateFtdcTraderApi("");
        api.RegisterSpi(new SpiTest());
        api.RegisterFront("tcp://180.168.146.187:10101");
        api.SubscribePublicTopic(0);
        api.SubscribePrivateTopic(0);
        api.Init();

        int id = 0, opCode = -1;

        // Sleep.
        sleep(1000);

        var auth = new CThostFtdcReqAuthenticateField();
        auth.UserProductInfo = "ctp4j-test";
        auth.UserID = "144287";
        auth.BrokerID = "9999";
        auth.AppID = "3430491819";
        auth.AuthCode = "0000000000000000";
        api.ReqAuthenticate(auth, ++id);

        sleep(1000);

        var login = new CThostFtdcReqUserLoginField();
        login.BrokerID = "9999";
        login.UserID = "144287";
        login.Password = "chb_1987_1013";
        api.ReqUserLogin(login, ++id);

        sleep(1000);

        var confirm = new CThostFtdcSettlementInfoConfirmField();
        confirm.CurrencyID = "CNY";
        confirm.BrokerID = "9999";
        confirm.AccountID = confirm.InvestorID = "144287";
        api.ReqSettlementInfoConfirm(confirm, ++id);

        sleep(1000);

        var qryInstrument = new CThostFtdcQryInstrumentField();
        qryInstrument.InstrumentID = "";
        api.ReqQryInstrument(qryInstrument, ++id);

        sleep(15000);

        var qryCommission = new CThostFtdcQryInstrumentCommissionRateField();
        qryCommission.InstrumentID = "c2101";
        qryCommission.BrokerID = "9999";
        qryCommission.InvestorID = "144287";
        api.ReqQryInstrumentCommissionRate(qryCommission, ++id);

        sleep(1000);

        var qryMargin = new CThostFtdcQryInstrumentMarginRateField();
        qryMargin.HedgeFlag = TThostFtdcCombHedgeFlagType.SPECULATION;
        qryMargin.InstrumentID = "c2101";
        qryMargin.BrokerID = "9999";
        qryMargin.InvestorID = "144287";
        api.ReqQryInstrumentMarginRate(qryMargin, ++id);

        sleep(1000);

        var qryAccount = new CThostFtdcQryTradingAccountField();
        qryAccount.BrokerID = "9999";
        qryAccount.AccountID = qryAccount.InvestorID = "144287";
        qryAccount.CurrencyID = "CNY";
        api.ReqQryTradingAccount(qryAccount, ++id);

        sleep(1000);

        var order = new CThostFtdcInputOrderField();
        order.UserID = "144287";
        order.AccountID = "144287";
        order.InvestorID = "144287";
        order.BrokerID = "9999";
        order.InstrumentID = "c2101";
        order.OrderPriceType = TThostFtdcOrderPriceTypeType.LIMIT_PRICE;
        order.CombOffsetFlag = TThostFtdcCombOffsetFlagType.OFFSET_OPEN;
        order.CombHedgeFlag = TThostFtdcCombHedgeFlagType.SPECULATION;
        order.VolumeTotalOriginal = 3;
        order.LimitPrice = 2230;
        order.Direction = TThostFtdcDirectionType.DIRECTION_BUY;
        order.OrderRef = Integer.toString(++id);
        order.VolumeCondition = TThostFtdcVolumeConditionType.ANY_VOLUME;
        order.TimeCondition = TThostFtdcTimeConditionType.GFD;
        order.MinVolume = 1;
        order.ContingentCondition = TThostFtdcContingentConditionType.IMMEDIATELY;
        order.StopPrice = 0;
        order.ForceCloseReason = TThostFtdcForceCloseReasonType.NOT_FORCE_CLOSE;
        order.IsAutoSuspend = 0;
        api.ReqOrderInsert(order, ++id);

        sleep(1000);

        var qryPosiDetail = new CThostFtdcQryInvestorPositionDetailField();
        qryPosiDetail.BrokerID = "9999";
        qryPosiDetail.InvestorID = "144287";
        qryPosiDetail.InstrumentID = "c2101";
        api.ReqQryInvestorPositionDetail(qryPosiDetail, ++id);

        sleep(1000);

        // Close position, then cancel the close order.
        order.CombOffsetFlag = TThostFtdcCombOffsetFlagType.OFFSET_CLOSE_TODAY;
        order.Direction = TThostFtdcDirectionType.DIRECTION_SELL;
        order.LimitPrice = 2230;
        order.VolumeTotalOriginal = 1;
        order.OrderRef = Integer.toString(++id);
        api.ReqOrderInsert(order, ++id);

        sleep(5000);
        System.out.println("\"" + rtnOrder.OrderSysID + "\"");

        var action = new CThostFtdcInputOrderActionField();
        action.BrokerID = "9999";
        action.UserID = action.InvestorID = "144287";
        action.OrderSysID = rtnOrder.OrderSysID;
        action.ExchangeID = "DCE";
        action.InstrumentID = "c2101";
        action.ActionFlag = TThostFtdcActionFlagType.DELETE;
        api.ReqOrderAction(action, ++id);
    }

    public static void main(String[] args) {
        new TraderApiTest().basic();
        try {
            new CountDownLatch(1).await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}