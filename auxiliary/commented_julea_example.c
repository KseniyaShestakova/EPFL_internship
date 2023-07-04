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

int
main(int argc, char** argv)
{
	// link to the batck - linked list of operations
	g_autoptr(JBatch) batch = NULL;
	// a DB-entry: contains a bson
	g_autoptr(JDBEntry) entry = NULL;
	// a DB-schema: contains bsons, hasg_table, array (index) and etc.
	g_autoptr(JDBSchema) schema = NULL;
	// a key-value pair abstraction
	g_autoptr(JKV) kv = NULL;
	// an object (whatever it means)
	g_autoptr(JObject) object = NULL;

	gchar const* hello_world = "Completely new sentence";
	guint64 nbytes;

	(void)argc;
	(void)argv;

	setlocale(LC_ALL, "C.UTF-8");

	/// \todo: this example does not clean up after itself and will only work if the object, kv pair and db entry do not exist already
	/// \todo: add more error checking

	batch = j_batch_new_for_template(J_SEMANTICS_TEMPLATE_DEFAULT);
	// JObject* j_object_new(gchar const* namespace, gchar const* name)
	object = j_object_new("hello", "world_");
	// JKV* j_kv_new(gchar const* namespace, gchar const* key)
	kv = j_kv_new("hello", "world_");
	// JDBSchema* j_db_schema_new(gchar const* namespace, gchar const* name, GError** error)
	schema = j_db_schema_new("hello", "world_", NULL);
	// gboolean j_db_schema_add_field(JBDSchema* schema, gchar const* name, JDBType type, GError** error)
	j_db_schema_add_field(schema, "hello", J_DB_TYPE_STRING, NULL);
	// JDBEntry* j_db_entry_new(JDBSchema* schema, GError** error)
	entry = j_db_entry_new(schema, NULL);
	/* gboolean j_db_enry_set_field(
	   				JDBEntry* entry, gchar const* name,
					gconstpointer value,
					guint64 length, --> only used if value_type defined in schema is binary
					GError** error)
	 */
	j_db_entry_set_field(entry, "hello", /*gconstpointer value*/ hello_world,
		             strlen(hello_world) + 1, NULL);
	// void j_object_create(JObject* object, JBatch* batch)
	j_object_create(object, batch);

	j_object_write(object, /*gconstpointer*/ hello_world,
		       /*length*/ strlen(hello_world) + 1,
		       /*offset*/ 0, 
		       /*bytes written*/ &nbytes,
		       /*JBatch* */batch); 
	//TODO is it a batch to which this operation is written??
	j_kv_put(kv, /*gpointer value*/ g_strdup(hello_world),
        	 strlen(hello_world) + 1,
		/*GDestroyNotify*/ g_free, // --> a function to correctly free stored date
		 batch);
	
	j_db_schema_create(/*JDBSchema*/ schema, // --> the schema to store
		       	/*JBatch*/ batch, // --> the batch to add this operation to
		       	/*Gerror error*/ NULL);
	j_db_entry_insert(/*JDBEntry* entry*/entry, // --> the entry to save
		       	batch,
		       	NULL);

	// after the batch was filled with operations, it should be executed
	if (j_batch_execute(batch))
	{
		// iterating through schemas
		g_autoptr(JDBIterator) iterator = NULL;
		// represents selections in, possibly joined, schemas
		g_autoptr(JDBSelector) selector = NULL;

		// a buffer to which we will read everything
		gchar buffer[128] = { '\0' };
		// g_autofree macro tells the compiler to add the required g_free(value)
		// before the return statement
		// typedef void* gpointer --> typedef in GLib
		g_autofree gpointer value = NULL;
		guint32 length = 0;
		g_autofree gchar* db_field = NULL;
		guint64 db_length = 0;

		// adds to the batch reading operation
		j_object_read(object, buffer, 128, 0, &nbytes, batch);

		if (j_batch_execute(batch))
		{
			printf("Object contains: %s (%" G_GUINT64_FORMAT " bytes)\n", buffer, nbytes);
		}

		// adds to the batch operation of getting value from key-value pair
		j_kv_get(kv, &value, &length, batch);

		if (j_batch_execute(batch))
		{
			printf("KV contains: %s (%" G_GUINT32_FORMAT " bytes)\n", (gchar*)value, length);
		}


		selector = j_db_selector_new(schema, J_DB_SELECTOR_MODE_AND, NULL);
		j_db_selector_add_field(selector,
			       		/*gchar const* name*/"hello",
				       	J_DB_SELECTOR_OPERATOR_EQ,
				        /*gconstpointer*/hello_world,
				        /*length*/ strlen(hello_world) + 1, NULL);
		iterator = j_db_iterator_new(schema, selector, NULL);

		while (j_db_iterator_next(iterator, NULL))
		{
			JDBType type;

			j_db_iterator_get_field(iterator, NULL, "hello", &type, (gpointer*)&db_field, &db_length, NULL);
			printf("DB contains: %s (%" G_GUINT64_FORMAT " bytes)\n", db_field, db_length);
		}
	}

	return 0;
}
