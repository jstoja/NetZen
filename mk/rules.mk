SRCDIR		 = src
OBJDIR		 = ../obj/$(TARGET)
HDRDIR		 = hdr
DESTDIR		 = ../bin
LIBDIR		 = ../lib

CC		 = cc
CXX		 = c++
LD		 = $(CC)
RM		 = rm -f
LN		 = ln -s
MKDIR		 = mkdir -p
AR		 = ar rc
RANLIB		 = ranlib
SYSTEM		 = ${shell uname -s}

ifeq "$(LANGUAGE)" "cpp"
LD		 = $(CXX)
endif

ifeq "$(SYSTEM)" "Darwin"
CC		:= $(CC) -arch i386
CXX		:= $(CC) -arch i386
endif

CFLAGS		+= -Wall -Wextra -std=c99 -I${HDRDIR} -ggdb
CXXFLAGS	+= -Wall -Wextra -I${HDRDIR} -ggdb
LDFLAGS		+= -L$(LIBDIR)
LIBS		+= 

ifeq "$(TYPE)" "lib"
OUTPUT		 = $(LIBDIR)/lib$(TARGET).a
else
OUTPUT		 = $(DESTDIR)/$(TARGET)
endif

SRC		:= ${addprefix $(SRCDIR)/,$(SOURCES)}
OBJ		:= ${addprefix $(OBJDIR)/,$(SOURCES)}
OBJ		:= $(OBJ:.cc=.o)
OBJ		:= $(OBJ:.c=.o)

$(OUTPUT):	$(OBJDIR) $(OBJ) $(DESTDIR) $(LIBDIR)
ifeq "$(TYPE)" "lib"
	$(AR) $(OUTPUT) $(OBJ)
	$(RANLIB) $(OUTPUT)
else
	$(LD) -o $(OUTPUT) $(LDFLAGS) $(OBJ) $(LIBS)
endif

$(OBJDIR)/%.o:	$(SRCDIR)/%.cc
	$(CXX) -o $@ $(CXXFLAGS) -c $<

$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(CC) -o $@ $(CFLAGS) -c $<

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(DESTDIR):
	$(MKDIR) $(DESTDIR)

$(LIBDIR):
	$(MKDIR) $(LIBDIR)

clean:
	$(RM) $(OBJ)

reset:		clean
	$(RM) $(OUTPUT)

new:		reset $(OUTPUT)

all:		$(OUTPUT)

.PHONY:		clean reset new all
