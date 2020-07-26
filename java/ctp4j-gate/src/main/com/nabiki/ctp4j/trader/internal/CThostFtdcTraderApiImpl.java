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
import com.nabiki.ctp4j.internal.InitConfig;
import com.nabiki.ctp4j.internal.SdkConfig;
import com.nabiki.ctp4j.jni.struct.*;
import com.nabiki.ctp4j.trader.CThostFtdcTraderApi;
import com.nabiki.ctp4j.trader.CThostFtdcTraderSpi;
import com.nabiki.iop.MessageType;

import java.io.File;
import java.util.Objects;

public class CThostFtdcTraderApiImpl extends CThostFtdcTraderApi {
    private final InitConfig initCfg = new InitConfig();
    private final SdkConfig sdkCfg;

    private IOPConnector connector;
    private CThostFtdcTraderSpi spi;
    private TradeSessionAdaptor sessionAdaptor;
    private TradeClientMessageAdaptor msgAdaptor;

    public CThostFtdcTraderApiImpl(String flow) {
        if (flow.trim().length() > 0)
            this.initCfg.Flow = flow.trim();
        else
            this.initCfg.Flow = ".";
        try {
            var f = new File("ctp4j-gate-trade.properties");
            if (f.exists())
                this.sdkCfg = SdkConfig.external(f);
            else
                this.sdkCfg = SdkConfig.resource("ctp4j-gate-trade");
        } catch (Throwable th) {
            throw new RuntimeException(th.getMessage(), th);
        }
        // Set mode.
        this.initCfg.isTrade = true;
    }

    @Override
    public String GetApiVersion() {
        return "1.0.0";
    }

    @Override
    public String GetTradingDay() {
        Objects.requireNonNull(this.msgAdaptor, "not initialized");
        return this.msgAdaptor.getTradingDay();
    }

    @Override
    public void Init() {
        this.sessionAdaptor = new TradeSessionAdaptor(this.spi);
        this.msgAdaptor = new TradeClientMessageAdaptor(this.spi);
        this.connector = IOPConnector.run(
                this.sdkCfg,
                this.initCfg,
                this.sessionAdaptor,
                this.msgAdaptor);
    }

    @Override
    public void Join() {
        Objects.requireNonNull(this.sessionAdaptor, "not initialized");
        this.sessionAdaptor.join();
    }

    @Override
    public void SubscribePrivateTopic(int type) {
        // nothing.
    }

    @Override
    public void SubscribePublicTopic(int type) {
        // nothing.
    }

    @Override
    public void RegisterFront(String frontAddress) {
        this.initCfg.Fronts.add(frontAddress);
    }

    @Override
    public void RegisterSpi(CThostFtdcTraderSpi spi) {
        this.spi = spi;
    }

    @Override
    public void Release() {
        Objects.requireNonNull(this.connector, "not initialized");
        this.connector.kill();
    }

    @Override
    public int ReqAuthenticate(
            CThostFtdcReqAuthenticateField reqAuthenticateField,
            int requestID) {
        this.connector.send(
                MessageType.REQ_AUTHENTICATE,
                reqAuthenticateField,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqUserLogin(
            CThostFtdcReqUserLoginField reqUserLoginField,
            int requestID) {
        this.connector.send(
                MessageType.REQ_LOGIN,
                reqUserLoginField,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqUserLogout(
            CThostFtdcUserLogoutField userLogout,
            int requestID) {
        this.connector.send(
                MessageType.REQ_LOGOUT,
                userLogout,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqSettlementInfoConfirm(
            CThostFtdcSettlementInfoConfirmField settlementInfoConfirm,
            int requestID) {
        this.connector.send(
                MessageType.REQ_SETTLEMENT,
                settlementInfoConfirm,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqOrderInsert(
            CThostFtdcInputOrderField inputOrder,
            int requestID) {
        this.connector.send(
                MessageType.REQ_ORDER_INSERT,
                inputOrder,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqOrderAction(
            CThostFtdcInputOrderActionField inputOrderAction,
            int requestID) {
        this.connector.send(
                MessageType.REQ_ORDER_ACTION,
                inputOrderAction,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqQryInstrument(
            CThostFtdcQryInstrumentField qryInstrument,
            int requestID) {
        this.connector.send(
                MessageType.QRY_INSTRUMENT,
                qryInstrument,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqQryInstrumentCommissionRate(
            CThostFtdcQryInstrumentCommissionRateField qryInstrumentCommissionRate,
            int requestID) {
        this.connector.send(
                MessageType.QRY_COMMISSION,
                qryInstrumentCommissionRate,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqQryInstrumentMarginRate(
            CThostFtdcQryInstrumentMarginRateField qryInstrumentMarginRate,
            int requestID) {
        this.connector.send(
                MessageType.QRY_MARGIN,
                qryInstrumentMarginRate,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqQryTradingAccount(
            CThostFtdcQryTradingAccountField qryTradingAccount,
            int requestID) {
        this.connector.send(
                MessageType.QRY_ACCOUNT,
                qryTradingAccount,
                Integer.toString(requestID));
        return 0;
    }

    @Override
    public int ReqQryInvestorPositionDetail(
            CThostFtdcQryInvestorPositionDetailField qryInvestorPositionDetail,
            int requestID) {
        this.connector.send(
                MessageType.QRY_POSI_DETAIL,
                qryInvestorPositionDetail,
                Integer.toString(requestID));
        return 0;
    }
}
