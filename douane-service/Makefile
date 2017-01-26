DAEMON_VERSION=$(shell cat VERSION)

CC=g++
PKGCONFIG=`pkg-config --cflags --libs liblog4cxx dbus-c++-1`
CFLAGS=-pedantic -Wall -W -g $(PKGCONFIG) -DDOUANE_VERSION=\"$(DAEMON_VERSION)\"
LDFLAGS=$(PKGCONFIG) -lboost_signals -lboost_system -lboost_filesystem -lboost_regex -lcrypto -lpthread

INSTALL=/usr/bin/install -c
BINDIR=$(DESTDIR)/opt/douane
PIDSDIR=$(DESTDIR)/opt/douane/pids
EXEC=bin/douaned

ODIR = obj
SDIR = src

OBJS= $(patsubst %,$(ODIR)/%, $(_OBJS))

_OBJS=freedesktop/desktop_file.o \
	freedesktop/desktop_files.o \
	dbus/dbus_server.o \
	dbus/douane.o \
	main.o \
	netlink_listener.o \
	netlink_message_handler.o \
	netlink_socket.o \
	network_activity.o \
	process.o \
	processes_manager.o \
	rule.o \
	rules_manager.o \
	socket.o \
	thread.o \
	service.o \
	log.o \
	tools.o



all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) $(LDFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJS) $(EXEC)

dbus:
	dbusxx-xml2cpp d-bus/org.zedroot.douane.xml --adaptor=org_zedroot_douane.h

install: $(EXEC)
	test -d $(BINDIR) || mkdir -p $(BINDIR)
	test -d $(DESTDIR)/etc/init.d/ || mkdir -p $(DESTDIR)/etc/init.d/
	test -d $(DESTDIR)/etc/dbus-1/system.d/ || mkdir -p $(DESTDIR)/etc/dbus-1/system.d/
	install -m 0500 $(EXEC) $(BINDIR)
	install -m 0755 src/init.d/douane $(DESTDIR)/etc/init.d/
	install -m 0644 src/system.d/org.zedroot.Douane.conf $(DESTDIR)/etc/dbus-1/system.d/
