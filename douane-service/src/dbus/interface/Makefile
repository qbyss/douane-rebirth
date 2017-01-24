DBUSXX_XML2CPP=$(shell which dbusxx-xml2cpp)
DBUS_SERVER_INTERFACE_SOURCE=org.zedroot.douane.server.xml
DBUS_CLIENT_INTERFACE_SOURCE=org.zedroot.douane.client.xml
CPP_ADAPTOR_NAME=org_zedroot_douane_adaptor.h
CPP_PROXY_NAME=org_zedroot_douane_proxy.h

all:
	make server
	make client

server:
	$(DBUSXX_XML2CPP) $(DBUS_SERVER_INTERFACE_SOURCE) --adaptor=$(CPP_ADAPTOR_NAME)

client:
	$(DBUSXX_XML2CPP) $(DBUS_CLIENT_INTERFACE_SOURCE) --proxy=$(CPP_PROXY_NAME)
