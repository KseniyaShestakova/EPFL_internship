/*
 * JULEA - Flexible storage framework
 * Copyright (C) 2019-2023 Michael Kuhn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <julea.h>
#include <julea-object.h>
#include <julea-kv.h>
#include <julea-db.h>

#include <locale.h>
#include <stdio.h>

int main() {
	setlocale(LC_ALL, "C.UTF-8");

	g_autoptr(JBatch) batch = NULL;
	g_autoptr(JObject) object = NULL;

	gboolean is_executed = false;
	guint64 bytes_written = 0;
	guint64 bytes_read = 0;

	gchar const* data = "Hello world!";
	gchar const* namespace = "ns-3";
	gchar const* name = "object-3";
	guint64 data_length = strlen(data) + 1;
	gchar buffer[256];

	gint64 modification_time = 0;
	guint64 size = 0;

	batch = j_batch_new_for_template(J_SEMANTICS_TEMPLATE_DEFAULT);
	object = j_object_new(namespace, name);

	j_object_create(object, batch); // calls backend_create
	//before calling backend_create name, namespace and handle must be extracted

	j_object_write(object, data, data_length, /*offset*/0, &bytes_written, batch);

	is_executed = j_batch_execute(batch);

	if (!is_executed) {
		printf("An error occured when writing the object!\n");
	} else {
		printf("%ld bytes written out of %ld\n", bytes_written, data_length);
	}
        //----------------------
	j_object_read(object, buffer, /*length*/128, /*offset*/0, &bytes_read, batch);
	j_object_status(object, &modification_time, &size, batch);

	is_executed = j_batch_execute(batch);
	
	if (!is_executed) {
		printf("Not executed!\n");
	} else {
		buffer[bytes_read] = 0;
		printf("%ld bytes read, read content: %s\n", bytes_read, buffer);
		printf("modification time: %ld\n", modification_time);
		printf("size: %ld\n", size);
	}
        //----------------
	gchar const* new_data = "//appended data";
	data_length = strlen(new_data) + 1;

	j_object_write(object, new_data, data_length,
		       /*offset*/bytes_read - 1, &bytes_written, batch);

	is_executed = j_batch_execute(batch);
	if (is_executed) {
		printf("%ld bytes written out of %ld\n", bytes_written, data_length);
	} else {
		printf("Not executed!\n");
	}
	//------------------------------------
	j_object_read(object, buffer, /*length*/128, /*offset*/0, &bytes_read, batch);
	j_object_status(object, &modification_time, &size, batch);


        is_executed = j_batch_execute(batch);

        if (!is_executed) {
                printf("Not executed!\n");
        } else {
                buffer[bytes_read] = 0;
                printf("%ld bytes read, read content: %s\n", bytes_read, buffer);
		printf("modification time: %ld\n", modification_time);
		printf("size: %ld\n", size);
        }


	j_object_delete(object, batch);
	is_executed = j_batch_execute(batch);

	if (!is_executed) {
		printf("Not executed!\n");
	} else {
		printf("Executed!\n");
	}
		

	return 0;
}
