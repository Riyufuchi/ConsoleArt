all:
	cd latex-doc && \
	lualatex ConsoleArt.tex && \
	makeglossaries ConsoleArt && \
	lualatex ConsoleArt.tex && \
	lualatex ConsoleArt.tex

.PHONY: all

