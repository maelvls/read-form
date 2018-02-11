all:
	gcc read_form_fields.c $(shell pkg-config --cflags --libs poppler-glib) $(shell pkg-config --cflags --libs gio-2.0) -o read_form_fields
clean:
	rm -f *.o read_form_fields
