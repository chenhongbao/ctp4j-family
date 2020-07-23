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

package com.nabiki.ctp4j.internal;

import com.nabiki.iop.*;

import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class IOPConnector {
    private IOPClient client;
    private ExternalProcess process;

    private IOPConnector() {
    }

    public static IOPConnector run(
            SdkConfig sdkCfg,
            InitConfig initCfg,
            ClientSessionAdaptor sessionAdaptor,
            ClientMessageAdaptor msgAdaptor) {
        var connector = new IOPConnector();
        if (sdkCfg.Mode == SdkConfig.AppMode.EXECUTABLE)
            connector.launchApp(sdkCfg, initCfg);
        try {
            connector.connectApp(sdkCfg, sessionAdaptor, msgAdaptor);
            return connector;
        } catch (IOException e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }

    public void kill() {
        if (this.process != null)
            this.process.kill();
        if (this.client != null)
            this.client.disconnect();
        this.process = null;
        this.client = null;
    }

    public <V> void send(
            MessageType type,
            V request,
            String requestID) {
        getSession().sendRequest(toMessage(type, request, requestID));
    }

    private <T> Message toMessage(MessageType type, T object, String requestID) {
        Objects.requireNonNull(object, "request null");
        Objects.requireNonNull(requestID, "request ID null");
        var message = new Message();
        message.Type = type;
        message.Body = object;
        message.RequestID = requestID;
        message.CurrentCount = 1;
        message.TotalCount = 1;
        return message;
    }

    private ClientSession getSession() {
        return this.client.getSession();
    }

    private void launchApp(SdkConfig sdkCfg, InitConfig initCfg) {
        this.process = new ExternalProcess(
                new File("ctp4j-gate.exe"),
                sdkCfg.CWD,
                sdkCfg.Redirect,
                getCommand(sdkCfg, initCfg));
        try {
            this.process.run();
        } catch (IOException e) {
            throw new RuntimeException(e.getMessage(), e);
        }
    }

    private void connectApp(
            SdkConfig sdkCfg,
            ClientSessionAdaptor sessionAdaptor,
            ClientMessageAdaptor msgAdaptor) throws IOException {
        this.client = IOP.createClient();
        this.client.setSessionAdaptor(sessionAdaptor);
        this.client.setMessageAdaptor(msgAdaptor);
        this.client.connect(
                InetSocketAddress.createUnresolved(sdkCfg.Host, sdkCfg.Port));
    }

    private List<String> getCommand(SdkConfig sdkCfg, InitConfig initCfg) {
        var r = new LinkedList<String>();
        r.add(getMode(initCfg.isTrade));
        if (initCfg.isUdp)
            r.add("--udp");
        if (initCfg.isMulticast)
            r.add("--multicast");
        r.add("--host");
        r.add(sdkCfg.Host);
        r.add("--port");
        r.add(Integer.toString(sdkCfg.Port));
        r.add("--flow");
        r.add(initCfg.Flow);
        r.add("--front");
        r.add(getFronts(initCfg.Fronts));
        return r;
    }

    private String getFronts(List<String> fronts) {
        if (fronts.size() == 0)
            throw new IllegalArgumentException("no front");
        if (fronts.size() == 1)
            return fronts.get(0);
        else {
            StringBuilder str = new StringBuilder(fronts.get(0));
            for (int i = 1; i < fronts.size(); ++i)
                str.append(",").append(fronts.get(i));
            return str.toString();
        }
    }

    private String getMode(boolean isTrade) {
        return isTrade ? "--trade" : "--md";
    }
}
