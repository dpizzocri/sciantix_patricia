############################################
##                                        ##
##            S C I A N T I X             ##
##            ---------------             ##
##                                        ##
##   Version: 0.1                         ##
##   Year   : 2016                        ##
##   Authors: D. Pizzocri and T. Barani   ##
##                                        ##
############################################
#    Makefile                              #
#    @barat, 17/05/2017                    #
############################################


#Initialization of useful variables

CC          := g++

TARGET      := sciantix.x

SRCDIR      := src
INCDIR      := include
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := src
SRCEXT      := C
DEPEXT      := d
OBJEXT      := o

CFLAGS      := -Wall -O
LIB         := -lm
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#####################################################################################

all: resources $(TARGET)

remake: cleaner all

resources: directories
	@cp $(RESDIR)/* $(TARGETDIR)/

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

clean:
	@$(RM) -rf $(BUILDDIR)
	@$(RM) -rf $(TARGETDIR)/*.$(SRCEXT)

cleaner: clean
	@$(RM) -rf $(TARGETDIR)

-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp
	@$(RM) -rf $(TARGETDIR)/*.$(SRCEXT)

.PHONY: all remake clean cleaner resources
