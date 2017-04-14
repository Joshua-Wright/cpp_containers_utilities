PYTHON  := python3
SOURCES := $(wildcard *.py)
OUTPUTS := $(SOURCES:%.py=%.h)

all: $(OUTPUTS) 

clean:
	rm  -f *.h

%.h: %.py
	$(PYTHON) $< > $@
