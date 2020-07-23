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

package com.nabiki.ctp4j.md.internal;

import com.nabiki.ctp4j.jni.struct.*;
import com.nabiki.ctp4j.md.CThostFtdcMdSpi;
import com.nabiki.iop.ClientMessageAdaptor;

import java.util.Objects;

public class MdClientMessageAdaptor extends ClientMessageAdaptor {
    private final CThostFtdcMdSpi spi;
    private String tradingDay;

    MdClientMessageAdaptor(CThostFtdcMdSpi spi) {
        Objects.requireNonNull(spi, "spi null");
        this.spi = spi;
    }

    private int getRequestID(String requestID) {
        return Integer.parseInt(requestID);
    }

    String getTradingDay() {
        return this.tradingDay;
    }

    @Override
    public void doRspSubscribeMarketData(
            CThostFtdcSpecificInstrumentField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnRspSubMarketData(
                rsp,
                info,
                getRequestID(requestID),
                current == total && total != 0);
    }

    @Override
    public void doRspUnsubscribeMarketData(
            CThostFtdcSpecificInstrumentField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnRspUnSubMarketData(
                rsp,
                info,
                getRequestID(requestID),
                current == total && total != 0);
    }

    @Override
    public void doRspDepthMarketData(
            CThostFtdcDepthMarketDataField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnRtnDepthMarketData(rsp);
    }
    @Override
    public void doRspReqLogin(
            CThostFtdcRspUserLoginField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.tradingDay = rsp.TradingDay;
        this.spi.OnRspUserLogin(
                rsp,
                info,
                getRequestID(requestID),
                current == total && total != 0);
    }

    @Override
    public void doRspReqLogout(
            CThostFtdcUserLogoutField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.tradingDay = null;
        this.spi.OnRspUserLogout(
                rsp,
                info,
                getRequestID(requestID),
                current == total && total != 0);
    }

    @Override
    public void doRspError(
            CThostFtdcRspInfoField rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnRspError(
                rsp,
                getRequestID(requestID),
                current == total && total != 0);
    }

    @Override
    public void doRspConnect(
            CThostFtdcConnect rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnFrontConnected();
    }

    @Override
    public void doRspDisconnect(
            CThostFtdcDisconnect rsp,
            CThostFtdcRspInfoField info,
            String requestID,
            String responseID,
            int current,
            int total) {
        this.spi.OnFrontDisconnected(rsp.Reason);
    }
}
