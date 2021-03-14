NAME	=	array

IDIR	=	include
SDIR	=	src
ODIR	=	obj
BDIR	=	.

SRCS	=	$(addprefix $(SDIR)/, main.cpp)
OBJS	=	$(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)
DEPS	=	$(OBJS:.o=.d)

CXX		=	clang++
LD		=	clang++

CXXFLAGS	=	-Wall -Wextra -Werror -I$(IDIR) -std=c++98 -pedantic-errors
DEPFLAGS	=	-MT $@ -MMD -MP -MF $(ODIR)/$*.d

COMPILE.cpp	=	$(CXX) $(DEPFLAGS) $(CXXFLAGS) -c
COMPILE.o	=	$(LD) $(LDFLAGS)

all:		$(BDIR)/$(NAME)

# Directories
$(ODIR) $(BDIR):
	@echo "MK $@"
	mkdir -p "$@"

# Dependencies
$(DEPS): $(ODIR)/%.d:
include $(wildcard $(DEPS))

# Objects
$(OBJS): $(ODIR)/%.o: $(SDIR)/%.cpp $(ODIR)/%.d | $(SDIR)
	@mkdir -p '$(@D)'
	@echo "CXX $<"
	$(COMPILE.cpp) $< -o $@

# Binaries
$(BDIR)/$(NAME):	$(OBJS) | $(BDIR)
	@echo "LD $@"
	$(COMPILE.o) $^ -o $@ $(LDLIBS)

re: fclean all

clean:
	rm -f $(OBJS) $(DEPS)
	@rmdir $(ODIR) || :

fclean: clean
	rm -f $(BDIR)/$(NAME)

.PHONY: re clean fclean

$(VERBOSE).SILENT:
