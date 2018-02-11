all:
	gcc read_form_fields.c $(shell pkg-config --cflags --libs poppler-glib) -o read_form_fields
clean:
	rm -f *.o read_form_fields