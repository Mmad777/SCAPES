#ifndef FLAGS_H
#define FLAGS_H


class Flags
{
public:
    static int ZF;  // Zero Flag
    static int SF;  // Sign Flag;

    static int IP;  // Instruction Pointer

    static void reset();
};

#endif // FLAGS_H
