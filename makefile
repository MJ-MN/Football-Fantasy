PROJECT_NAME:= footballFantasy.out
CC          := g++ --std=c++11
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := build
BINDIR      := bin
EXE_FILE    := $(BINDIR)/$(PROJECT_NAME)
SOURCES     := $(shell find $(SRCDIR) -type f -name *.c*)
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
INC         := -I $(INCDIR)

$(EXE_FILE): $(BUILDDIR) $(BINDIR) $(OBJECTS)
	$(CC) -o $(EXE_FILE) $(OBJECTS)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c*
	@mkdir -p $(dir $@)
	$(CC) $(INC) -c $< -o $@
	@$(CC) $(INC) -M $< -MT $@ > $(@:.o=.td)
	@cp $(@:.o=.td) $(@:.o=.d); 
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
