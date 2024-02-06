SUMMARY = "hello world application"
DESCRIPTION = "hello world application which uses library recipe for libdumpinfo"
SECTION = "examples"
DEPENDS += "library"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"
SRC_URI = "file://hello_world.c \
	file://hello_world_init \
	file://hello_world_c.service \
	"

do_compile () {
	${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/hello_world.c -o ${WORKDIR}/hello_world -l:libdumpinfo.so.0.1
}

do_install () {
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/hello_world ${D}${sbindir}/

	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/hello_world ${D}${bindir}/

	install -d ${D}${sysconfdir}/init.d
	cat ${WORKDIR}/hello_world_init | \
	  sed -e 's,/etc,${sysconfdir},g' \
	      -e 's,/usr/sbin,${sbindir},g' \
	      -e 's,/var,${localstatedir},g' \
	      -e 's,/usr/bin,${bindir},g' \
	      -e 's,/usr,${prefix},g' > ${D}${sysconfdir}/init.d/hello_world_init
	chmod a+x ${D}${sysconfdir}/init.d/hello_world_init

	install -d ${D}${systemd_unitdir}/system/
	install -m 0644 ${WORKDIR}/hello_world_c.service ${D}${systemd_unitdir}/system/
	install -d ${D}${libdir}/systemd/system/
	install -m 0644 ${WORKDIR}/hello_world_c.service ${D}${libdir}/systemd/system/
}

inherit update-rc.d systemd 

RDEPENDS:${PN} = "library initscripts"

FILES:${PN} += "${sbindir}/hello_world"
FILES:${PN} += "${bindir}/hello_world"
FILES:${PN} += "${sysconfdir}/init.d/hello_worl_init"
FILES:${PN} += "${systemd_unitdir}/system/hello_world_c.service"
FILES:${PN} += "${libdir}/systemd/system/hello_world_c.service"

# init.d
CONFFILES:${PN} += "${sysconfdir}/init.d/hello_worl_init"
FILES:${PN}-init += "${sysconfdir}/init.d/hello_worl_init"

# Set the systemd service file for the recipe
SYSTEMD_SERVICE_${PN} = "hello_world_c.service"
FILES:${PN}-init += "${systemd_unitdir}/system/hello_world_c.service"
FILES:${PN}-init += "${libdir}/systemd/system/hello_world_c.service"


INITSCRIPT_NAME = "hello_world_init"
INITSCRIPT_PARAMS = "start 99 S ."



