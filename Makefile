CXX			= g++
RM			= rm -f
MD			= mkdir -p
CPPFLAGS	= -I/usr/include/opencv4
LDLIBS		= -lopencv_core \
			  -lopencv_videoio \
			  -lopencv_imgcodecs

ODIR		= obj
_OBJ		= main.o \
			  mwpimage.o
OBJ			= $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: $(ODIR) clean distclean

all: $(ODIR) mwp

$(ODIR):
	$(MD) $(ODIR)

obj/%.o: %.cpp
	$(CXX) -c -o $@ $< $(CPPFLAGS)

mwp: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDLIBS)

clean:
	$(RM) -r $(ODIR)

disclean: clean
	$(RM) mwp

install: all
	install -m 755 mwp /usr/local/bin/