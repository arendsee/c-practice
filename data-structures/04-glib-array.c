#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

int main(){
    /*
     * A GPtrArray type is simply the structure below:
       > struct GPtrArray {
       >   gpointer *pdata;
       >   guint	    len;
       > };
     * It will grow dynamically as needed.
    */
    GPtrArray *array;

    // This works as an endless sack of things
    array = g_ptr_array_new();

    gchar * a = "alice";
    gchar * b = "bob";
    gint  * c = (void*)123;

    g_ptr_array_add(array, (gpointer) a);
    g_ptr_array_add(array, (gpointer) b);
    g_ptr_array_add(array, (gpointer) c);

    // Given the structure of GPtrArray, we can do this
    printf("%s %s %d\n", array->pdata[0], array->pdata[1], array->pdata[2] + 1);

    // Or we can use the provided functions
    printf("%s %s\n", g_ptr_array_index(array, 0), g_ptr_array_index(array, 1));

    g_ptr_array_free(array, TRUE);
    exit(EXIT_SUCCESS);
}
