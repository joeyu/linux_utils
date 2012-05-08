#!/usr/bin/python

import re

re_vdso = re.compile(r"^([a-z0-9]+)-.+\[vdso\]\s*$")
re_vsyscall = re.compile(r"^([a-z0-9]+)-.+\[vsyscall\]\s*$")
addr_vdso = 0;
addr_vsyscall = 0;

f = open('/proc/self/maps', 'r')
for line in f:
    m = re_vdso.match(line)
    if m:
        print line
        addr_vdso = int(m.group(1), 16)
    m = re_vsyscall.match(line)
    if m:
        print line
        addr_vsyscall = int(m.group(1), 16)
f.close()

print addr_vdso
print addr_vsyscall
f = open('/proc/self/mem', 'r')
f.seek(addr_vdso)
data_vdso = f.read(4096)
f.seek(addr_vsyscall)
data_vsyscall = f.read(4096)
f.close()

f = open('linux-vdso.so.1','w')
f.write(data_vdso);
f.close()

f = open('linux-vsyscall.so.1','w')
f.write(data_vsyscall);
f.close()
