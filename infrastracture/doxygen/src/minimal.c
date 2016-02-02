/**
 * @file minimal.c
 * @author My Self
 * @date 9 Sep 2012
 * @brief File containing example of doxygen usage for quick reference.
 *
 * Here typically goes a more extensive explanation of what the header
 * defines. Doxygens tags are words preceeded by either a backslash @\
 * or by an at symbol @@.
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

/** @brief Cast an int as a long
 *
 *  Here is an unnecessarily long description of a trivial
 *  function. It is pretty long. So long it needs several
 *  sentences. It contains lots of awesome details.
 *
 *  @param a integer to be converted to long
 */
long int_2_long(int a){
    return (long) a;
}

int main(){
    return 0;
}
