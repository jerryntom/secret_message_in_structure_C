# secret_message_in_structure_C
Using unused bytes of structure to hide message

Let's have a look at our example bin file:
```
Enter file name: example_structures.bin⏎
Ninety percent of games lose money; 10 percent make a lot of money. And there's a consistency around the competitive advantages you create, so if you can actually learn how to do the art, the design, and the programming, you would be consistently very profitable. - Gabe Newell"Technology presumes there's just one right way to do things and there never is. " - Robert M. PirsigThe opposite of love is not hate, it's indifference. The opposite of art is not ugliness, it's indifference. The opposite of faith is not heresy, it's indifference. And the opposite of life is not death, it's indifference. - Elie Wiesel"Technology is ruled by two types of people: those who manage what they do not understand, and those who understand what they do not manage." - Mike TroutNever doubt that a small group of thoughtful, committed, citizens can change the world. Indeed, it is the only thing that ever has. - Margaret MeadEveryday life is like programming, I guess. If you love something you can put beauty into it. - Donald KnuthI absolutely don't think a sentient artificial intelligence is going to wage
```
How does it work? Our bin file is simply a sequence of structures written in binary. We are moving through the file looking for spare bytes. Why do we have 11 spare bytes?
```
struct message_t
{
    char a;
    double b;
    int c;
};
```
Take a look at the structure upper. We can tell that our data takes 13 bytes of memory but it doesn't mean that our structure takes that amount of memory.
Our biggest variable is b, which is a type of double, and the double variable takes 8 bytes of memory. Structures in C use memory optimization, which means
that actually, every variable in our structure takes 8 bytes of memory. That sums to 24 bytes. 
