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

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;
import java.util.ResourceBundle;

public class SdkConfig {
    enum AppMode {
        INET, EXECUTABLE
    }

    public AppMode Mode;
    public String Host;
    public int Port;
    public File CWD;
    public File Redirect;

    private SdkConfig() {}

    public static SdkConfig load(File config) throws IOException {
        var cfg = internal();
        var props = new Properties();
        props.load(new FileInputStream(config));
        var mode = props.getProperty("mode", "executable");
        if (mode.compareTo("inet") == 0)
            cfg.Mode = AppMode.INET;
        else if (mode.compareTo("executable") == 0)
            cfg.Mode = AppMode.EXECUTABLE;
        cfg.CWD = new File(props.getProperty("cwd", "."));
        cfg.Redirect = new File(props.getProperty("redirect",
                "ctp4j-redirect.txt"));
        cfg.Host = props.getProperty("host", "localhost");
        cfg.Port = Integer.parseInt(props.getProperty("port",
                "9036"));
        return cfg;
    }

    public static SdkConfig load() {
        return internal();
    }

    private static SdkConfig internal() {
        var cfg = new SdkConfig();
        ResourceBundle resource = ResourceBundle
                .getBundle("com/nabiki/ctp4j/internal/resources/ctp4j-gate");
        var mode = resource.getString("mode");
        if (mode.compareTo("inet") == 0)
            cfg.Mode = AppMode.INET;
        else if (mode.compareTo("executable") == 0)
            cfg.Mode = AppMode.EXECUTABLE;
        cfg.CWD = new File(resource.getString("cwd"));
        cfg.Redirect = new File(resource.getString("redirect"));
        cfg.Host = resource.getString("host");
        cfg.Port = Integer.parseInt(resource.getString("port"));
        return cfg;
    }
}
