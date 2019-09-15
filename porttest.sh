#!/bin/sh

PORTSDIR=/usr/ports

PORTS="emulators/virtualbox-ose emulators/virtualbox-ose-additions"

set -ex

cd /usr
#ls -al ports
mv ports ports.old
#svnlite co svn://svn.freebsd.org/ports/head ports
#portsnap --interactive fetch extract
git clone --depth=1 https://github.com/freebsd/freebsd-ports ports

cd ${CIRRUS_WORKING_DIR}
for p in `cat list.txt`
do
	if [ -d ${PORTSDIR}/${p}/ ]; then
		rm -fr ${PORTSDIR}/${p}/*
	else
		mkdir -p ${PORTSDIR}/${p}
	fi
        cp -R ./${p}/* ${PORTSDIR}/${p}/
done

mkdir /usr/ports/distfiles

df -h

echo "NO_ZFS=yes" >> /usr/local/etc/poudriere.conf
echo "ALLOW_MAKE_JOBS=yes" >> /usr/local/etc/poudriere.conf
sed -i.bak -e 's,FREEBSD_HOST=_PROTO_://_CHANGE_THIS_,FREEBSD_HOST=https://download.FreeBSD.org,' /usr/local/etc/poudriere.conf
mkdir -p /usr/local/poudriere

poudriere jail -c -j jail -v `uname -r`
poudriere ports -c -f none -m null -M /usr/ports

# use an easy port to bootstrap pkg repo
poudriere bulk -t -j jail net/nc

cd /usr/ports
for p in ${PORTS}
do
	make -f ${PORTSDIR}/${p}/Makefile all-depends-list | \
		sed -e "s,${PORTSDIR}/,," | \
		xargs sudo pkg fetch -y \
			-o /usr/local/poudriere/data/packages/jail-default/.latest/

	poudriere testport -j jail ${p}
done
