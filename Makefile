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

VPATH    = $(SRCDIR)
CFLAGS   =  -Wall -Werror -g -ggdb -fpic -fmessage-length=0 -pthread

OBJS     =  stringc.o
LIBS     =  -L/usr/local/lib -lstringc -lpthread
TARGET   =  libstringc.$(SOEXT)

all: $(TARGET)
	@echo "*** Build stringc OK ***"

$(TARGET): $(OBJS)
	$(CC) -shared $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
%.o: %.c $(SRCDIR)
	$(CC) -shared $(CFLAGS) -c $<	
	
doc:
	doxygen $(SRCDIR)/doxygen.conf
	( cd $(SRCDIR)/$(DOCDIR)/latex && make )
	cp $(SRCDIR)/$(DOCDIR)/latex/refman.pdf \
		$(SRCDIR)/$(DOCDIR)/stringc.pdf

test: $(TARGET)
	$(CC) $(CFLAGS) \
		-o stringc_test \
		-L$(SRCDIR)/_Debug \
		-lstringc \
		$(SRCDIR)/stringc_test.c
	sh -c "LD_LIBRARY_PATH=./ ./stringc_test"
	
install: all
ifneq ($(OS),GNU/Linux)
	cp $(TARGET) /usr/local/lib/
else
	cp libstringc.so /usr/local/lib/libstringc.so.0.1.0
	chmod 0755       /usr/local/lib/libstringc.so.0.1.0	
	( cd /usr/local/lib && ln -sf libstringc.so.0.1.0 libstringc.so.0.1 )
	( cd /usr/local/lib && ln -sf libstringc.so.0.1.0 libstringc.so.0   )
	( cd /usr/local/lib && ln -sf libstringc.so.0.1.0 libstringc.so     )
	cp -rf $(SRCDIR)/stringc /usr/local/include/
endif
	cp -rf ../stringc /usr/local/include/

endif
