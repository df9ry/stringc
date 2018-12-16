#   Project stringc
#   Copyright (C) 2019 tania@df9ry.de
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Affero General Public License as
#   published by the Free Software Foundation, either version 3 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Affero General Public License for more details.
#
#   You should have received a copy of the GNU Affero General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
ifeq (,$(filter _%,$(notdir $(CURDIR))))
include target.mk
else

VPATH = $(SRCDIR)

CFLAGS   =  -Wall -Werror -g -ggdb -fpic -fmessage-length=0 -pthread

LDFLAGS  =  -Wall -Werror -g -ggdb -fpic -fmessage-length=0 -pthread
			
OBJS     =  stringc.o
			
LIBS     =  -lpthread

TARGET   =  libstringc.so

$(TARGET):  $(OBJS)
	$(CC) -shared $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.c $(SRCDIR)
	$(CC) $(CFLAGS) -c $<	
	
all: $(TARGET) test
	echo "Build OK"

doc:
	doxygen $(SRCDIR)/doxygen.conf
	( cd $(SRCDIR)/_Documentation/latex && make )
	cp $(SRCDIR)/_Documentation/latex/refman.pdf \
		$(SRCDIR)/_Documentation/stringc.pdf

test: $(TARGET)
	$(CC) -Wall -Werror -g -ggdb -fmessage-length=0 -o stringc_test \
		-L$(SRCDIR)/_Debug \
		-lstringc \
		$(SRCDIR)/stringc_test.c
	sh -c "LD_LIBRARY_PATH=./ ./stringc_test"
	
install: libstringc.so test doc
	sudo cp libstringc.so /usr/local/lib/libstringc.so.0.1.0
	sudo chown root:staff /usr/local/lib/libstringc.so.0.1.0	
	sudo chmod 0755       /usr/local/lib/libstringc.so.0.1.0	
	( cd /usr/local/lib && sudo ln -sf libstringc.so.0.1.0 libstringc.so.0.1 )
	( cd /usr/local/lib && sudo ln -sf libstringc.so.0.1.0 libstringc.so.0   )
	( cd /usr/local/lib && sudo ln -sf libstringc.so.0.1.0 libstringc.so     )
	sudo cp stringc_test /usr/local/bin
	sudo chown root:staff /usr/local/bin/stringc_test
	sudo cp -rf $(SRCDIR)/stringc /usr/local/include
	sudo chown -R root:staff /usr/local/include/stringc
	sudo mkdir -p /usr/local/doc
	sudo cp $(SRCDIR)/_Documentation/stringc.pdf /usr/local/doc
	
endif
