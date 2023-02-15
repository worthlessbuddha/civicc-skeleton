.PHONY: run clean

%.s: %.cvc
	civcc -o $@ $^

%.out: %.s
	civas -o $@ $^

run: core.out coreio.out array.out main.out
	civvm $^

clean:
	rm -f *.cpp *.s *.out
