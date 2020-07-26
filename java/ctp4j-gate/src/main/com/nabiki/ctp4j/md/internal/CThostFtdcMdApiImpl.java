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

import com.nabiki.ctp4j.internal.IOPConnector;
import com.nabiki.ctp4j.internal.InitConfig;
import com.nabiki.ctp4j.internal.SdkConfig;
import com.nabiki.ctp4j.jni.struct.CThostFtdcReqUserLoginField;
import com.nabiki.ctp4j.jni.struct.CThostFtdcSubMarketDataField;
import com.nabiki.ctp4j.jni.struct.CThostFtdcUnsubMarketDataField;
import com.nabiki.ctp4j.jni.struct.CThostFtdcUserLogoutField;
import com.nabiki.ctp4j.md.CThostFtdcMdApi;
import com.nabiki.ctp4j.md.CThostFtdcMdSpi;
import com.nabiki.iop.MessageType;

import java.io.File;
import java.util.Objects;

public class CThostFtdcMdApiImpl extends CThostFtdcMdApi {
    private final InitConfig initCfg = new InitConfig();
    private final SdkConfig sdkCfg;

    private IOPConnector connector;
    private CThostFtdcMdSpi spi;
    private MdSessionAdaptor sessionAdaptor;
    private MdClientMessageAdaptor msgAdaptor;

    public CThostFtdcMdApiImpl(String flow, boolean udp, boolean multicast) {
        if (flow.trim().length() > 0)
            this.initCfg.Flow = flow.trim();
        else
            this.initCfg.Flow = ".";
        this.initCfg.isUdp = udp;
        this.initCfg.isMulticast = multicast;
        try {
            var f = new File("ctp4j-gate-md.properties");
            if (f.exists())
                this.sdkCfg = SdkConfig.external(f);
            else
                this.sdkCfg = SdkConfig.resource("ctp4j-gate-md");
        } catch (Throwable th) {
            throw new RuntimeException(th.getMessage(), th);
        }
        // Set mode.
        this.initCfg.isTrade = false;
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
        this.sessionAdaptor = new MdSessionAdaptor(this.spi);
        this.msgAdaptor = new MdClientMessageAdaptor(this.spi);
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
    public void RegisterFront(String frontAddress) {
        this.initCfg.Fronts.add(frontAddress);
    }

    @Override
    public void RegisterSpi(CThostFtdcMdSpi spi) {
        this.spi = spi;
    }

    @Override
    public void Release() {
        Objects.requireNonNull(this.connector, "not initialized");
        this.connector.kill();
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
    public int SubscribeMarketData(String[] instrumentID, int count) {
        var sub = new CThostFtdcSubMarketDataField();
        sub.InstrumentID = instrumentID;
        this.connector.send(
                MessageType.SUB_MD,
                sub,
                Integer.toString(0));
        return 0;
    }

    @Override
    public int UnSubscribeMarketData(String[] instrumentID, int count) {
        var unsub = new CThostFtdcUnsubMarketDataField();
        unsub.InstrumentID = instrumentID;
        this.connector.send(
                MessageType.UNSUB_MD,
                unsub,
                Integer.toString(0));
        return 0;
    }
}
