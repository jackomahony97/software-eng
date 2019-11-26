all: compile run clean

compile: main.c
	@gcc main.c tokenizer.c infix2postfix.c codegenerator.c virtualmachine.c -o maintest -lm # Compile programs

run:
	@./maintest # Run calculator

clean:
	@rm ./maintest # Remove maintest file, allows program to be immediately rerun

test:
	
