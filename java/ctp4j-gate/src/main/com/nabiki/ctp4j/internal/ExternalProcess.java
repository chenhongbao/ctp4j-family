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
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class ExternalProcess {
    private final File executable, workdingDir, redirect;
    private final List<String> args;

    private Process proc;

    public ExternalProcess(
            File executable,
            File workingDir,
            File redirect,
            List<String> args) {
        this.executable = executable;
        this.workdingDir = workingDir;
        this.redirect = redirect;
        this.args = args;
    }

    public void run() throws IOException {
        if (this.proc != null && this.proc.isAlive())
            throw new IllegalStateException("process has started");
        if (!this.workdingDir.isDirectory())
            throw new IllegalStateException("working directory not directory");
        var cmd = new LinkedList<String>();
        cmd.add(getExecutablePath());
        cmd.addAll(this.args);
        this.proc = new ProcessBuilder()
                .directory(this.workdingDir)
                .command(cmd)
                .redirectError(getRedirectFile())
                .redirectOutput(getRedirectFile())
                .start();
    }

    private String getExecutablePath() {
        if (!this.executable.isFile())
            throw new IllegalStateException("executable not file");
        return this.executable.getAbsolutePath();
    }

    private File getRedirectFile() {
        try {
            if (!this.redirect.exists() && !this.redirect.createNewFile())
                throw new IllegalStateException("redirect non file");
        } catch (IOException e) {
            throw new IllegalStateException("can't create redirect file");
        }
        return this.redirect;
    }

    public void kill() {
        if (this.proc == null)
            throw new IllegalStateException("no process");
        if (!this.proc.isAlive())
            throw new IllegalStateException("process has stopped");
        try {
            this.proc.destroyForcibly();
            this.proc.waitFor(15, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            this.proc = null;
        }
    }
}
