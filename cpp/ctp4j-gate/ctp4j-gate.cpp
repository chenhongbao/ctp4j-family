#pragma comment (lib, "nanomsg.lib")

#include "trade.h"
#include "md.h"

constexpr auto help_msg = R"(
--trade        trade mode, logins to trader front
--md           market data mode, logins to md front
--udp          UDP protocol, `false` by default
--multicast    multicast communication mode, `false` by default
--host  <host> host name of ipv4 address, by default it is `localhost`
--port  <port> port, by default it is `9036`
--flow	<directory>
               flow directory, `.` by default
--front <address0>,<address1>,...
               front addresses(no space in between)
-- help        print help info
)";

int main(int argc, char** argv)
{
    ::args args(argc, argv);
    if (args.is_help()) {
        printf("%s", help_msg);
        exit(0);
    }
    else {
        switch (args.get_mode()) {
        case app_mode::trade:
        {
            trade_server trade(args);
            trade.run();
        }
        break;
        case app_mode::md:
        {
            md_server md(args);
            md.run();
        }
        break;
        default:
            print("no valid mode, `--help`");
            exit(-1);
        }
        return 0;
    }
}
