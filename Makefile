# ed2 Makefile - The smaller ed for Plus Linux

ed2:
        cc main.c -o ed2
install:
        cp ed2 /usr/bin/
        chmod 755 /usr/bin/ed2
        echo && echo "Install Done" && echo
uninstall:
        rm -f /usr/bin/ed2
