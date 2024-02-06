SUMMARY = "hello world application patch."
DESCRIPTION = "hello world application which uses patch to its code."
SECTION = "examples"
LICENSE = "CLOSED"

FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += " file://hello_world-c.patch;patchdir=${WORKDIR}/ "

