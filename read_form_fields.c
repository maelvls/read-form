#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <poppler.h>

#define DEBUG 0

// A small helper function for handling arguments of the form '--arg=value'.
char* dashdashequal(const char* expected, char* argv) {
    // Var. name:         Example:
    // argv               --beginning=ending
    // argv_beginning     --beginning
    // argv_ending        ending
    char *argv_ending = strchr(argv,'=') + 1;
    if (argv_ending == NULL) {
        // if argv_ending is NULL, it means that strchr did not find '=',
        // then the parameter is wrong
        fprintf(stderr,"error: '%s' should be of the form '%s=ARG'\n",argv,argv);
        exit(1);
    }
    char argv_beginning[100];
    stpncpy(argv_beginning, argv, strlen(expected));
    if (0 != strcmp(argv_beginning,expected)) {
        return NULL;
    }
    return argv_ending;
}

bool is_in(char* str, char **str_array, int N) {
    for (int i = 0; i < N; i++) {
        if (strcmp(str,str_array[i]) == 0)
            return true;
    }
    return false;
}

// If you want to mutate str in-place, you can put str and str_stripped with
// the same pointer. I wrote this function because I needed a way to remove
// the \uFEFF (Byte Order Mark) which was pollutin the field names.
void strip(char* str, char* str_stripped, char* token) {
    int i = 0, i_stripped = 0;
    // printf("'%s'\n", str);
    while(i < strlen(str)) {
        // printf("'%c'\n", str[i]);
        int j = 0;
        while (i+j < strlen(str) && j < strlen(token) && str[i+j] == token[j]) j++;
        if (j == strlen(token)) {
            i += strlen(token);
        }
        str_stripped[i_stripped] = str[i];
        i++;
        i_stripped++;
    }
    str_stripped[i_stripped]='\0'; // terminate the string properly
}

int main(int argc, char **argv)
{
    char help[] =
    "Get the form field contents from a PDF. It uses poppler. The output looks\n"
    "like PDFtk's dump_data_fields_utf8.\n"
    "\n"
    "Usage:\n"
    "  read_form_fields (<file> | -)\n"
    "  read_form_fields --help\n"
    "\n"
    "Options:\n"
    "  <file> is the name of the file\n"
    "  -h --help       Show this screen.\n"
    "Details of output:\n"
    "  Only 'text' fields have their value displayed.\n";

    char f_name[256] = "";
    char *arg;

    for (int i = 1; i < argc; i++) {
        if (0==strcmp("--help",argv[i]) || 0==strcmp("-h",argv[i])) {
            fprintf(stdout,"%s",help);
            exit(0);
        }
        else if (0==strcmp("-",argv[i])) {
            strcpy(f_name, "/dev/stdin");
        }
        else {
            strcpy(f_name, argv[i]);
        }
    }
    if (strlen(f_name) == 0) {
        fprintf(stderr,"usage: you must give a file name (or - for stdin)\n");
        exit(124);
    }

    GError *error=NULL;
    gchar *uri;
    PopplerDocument *document;

    uri = g_filename_to_uri (f_name, NULL, &error);
    if (uri == NULL) {
        printf("error: poppler fail opening '%s': %s\n", f_name, error->message);
        return 1;
    }
    if (DEBUG) printf("uri: %s\n", uri);
    document = poppler_document_new_from_file (uri, NULL, &error);
    if (document == NULL) {
        printf("error: poppler fail: %s\n", error->message);
        return 2;
    }

    int count = 0;
    PopplerPage *page = NULL;
    for (int id_page = 0; id_page < poppler_document_get_n_pages(document); id_page++) {
        GList *list = poppler_page_get_form_field_mapping(poppler_document_get_page(document,id_page));
        for (int i=0; i<g_list_length(list); i++) {
            if (i > 0) printf("---\n");

            PopplerFormFieldMapping *f = g_list_nth_data(list, i);
            // printf("field found, id: %d, name: %s\n",poppler_form_field_get_id(f->field),poppler_form_field_get_name(f->field));
            PopplerFormFieldType type = poppler_form_field_get_field_type(f->field);

            printf("FieldType: ");
            switch(type) {
                case POPPLER_FORM_FIELD_UNKNOWN: printf("unkonwn"); break;
                case POPPLER_FORM_FIELD_BUTTON: printf("button"); break;
                case POPPLER_FORM_FIELD_TEXT: printf("text"); break;
                case POPPLER_FORM_FIELD_CHOICE: printf("choice"); break;
                case POPPLER_FORM_FIELD_SIGNATURE: printf("signature"); break;
            }
            printf("\n");

            if (strlen(poppler_form_field_get_name(f->field))>0) {
                char* txt = poppler_form_field_get_name(f->field);
                if (txt != NULL) {
                    strip(txt,txt,"\uFEFF");
                    printf("FieldName: %s\n", txt);
                } else {
                    printf("FieldName:\n");
                }
            }

            if (type == POPPLER_FORM_FIELD_TEXT) {
                gchar* txt = poppler_form_field_text_get_text(f->field);
                if (txt != NULL) {
                    strip(txt,txt,"\uFEFF");
                    printf("FieldValue: %s", txt);
                } else {
                    printf("FieldValue:");
                }
            } else {
                printf("FieldValue:");
            }
            printf("\n");
            count++;
        }
    }
    if (DEBUG) printf("number of fields: %d\n", count);

    return 0;
}

