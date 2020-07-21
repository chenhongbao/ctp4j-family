#pragma comment (lib, "Ws2_32.lib")

#include "trade.h"
#include "md.h"
#include "server.h"

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
        ::service* service_ptr;
        try {
            switch (args.get_mode()) {
            case app_mode::trade:
                service_ptr = new trade_service(args);
                break;
            case app_mode::md:
                service_ptr = new md_service(args);
                break;
            default:
                print("invalid mode, `--help`");
                exit(-1);
            }
            ::server svr(args, *service_ptr);
            svr.run();
        }
        catch (std::exception& e) {
            print(e.what());
        }
        catch (...) {
            print("unknown error");
        }
        return 0;
    }
}
