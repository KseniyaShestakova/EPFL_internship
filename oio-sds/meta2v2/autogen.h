/*
Copyright (C) 2017-2017 OpenIO SAS, as part of OpenIO SDS

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* AUTOGENERATED */
#ifndef GENERATED_H
# define GENERATED_H 1
# include <glib.h>
# include <sqlite3.h>
# include <meta2v2/generic.h>

extern const struct bean_descriptor_s descr_struct_CONTENTS_HEADERS;
extern const struct bean_descriptor_s descr_struct_CHUNKS;
extern const struct bean_descriptor_s descr_struct_PROPERTIES;
extern const struct bean_descriptor_s descr_struct_ALIASES;
extern const gchar *schema;


struct fields_CONTENTS_HEADERS_s;
struct bean_CONTENTS_HEADERS_s;

struct fields_CHUNKS_s;
struct bean_CHUNKS_s;

struct fields_PROPERTIES_s;
struct bean_PROPERTIES_s;

struct fields_ALIASES_s;
struct bean_ALIASES_s;

/* Loader and Saver for CONTENTS_HEADERS */

GError* CONTENTS_HEADERS_load(sqlite3 *db, const gchar *clause,
		GVariant **params, on_bean_f cb, gpointer u);

/* Loader and Saver for CHUNKS */

GError* CHUNKS_load(sqlite3 *db, const gchar *clause,
		GVariant **params, on_bean_f cb, gpointer u);

/* Loader and Saver for PROPERTIES */

GError* PROPERTIES_load(sqlite3 *db, const gchar *clause,
		GVariant **params, on_bean_f cb, gpointer u);

/* Loader and Saver for ALIASES */

GError* ALIASES_load(sqlite3 *db, const gchar *clause,
		GVariant **params, on_bean_f cb, gpointer u);

/* Getters and Setters for CONTENTS_HEADERS */

GByteArray * CONTENTS_HEADERS_get_id(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_id(struct bean_CONTENTS_HEADERS_s *bean, GByteArray * v);
void CONTENTS_HEADERS_set2_id(struct bean_CONTENTS_HEADERS_s *bean, const guint8 *v, gsize vlen);

GByteArray * CONTENTS_HEADERS_get_hash(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_hash(struct bean_CONTENTS_HEADERS_s *bean, GByteArray * v);
void CONTENTS_HEADERS_set2_hash(struct bean_CONTENTS_HEADERS_s *bean, const guint8 *v, gsize vlen);
void CONTENTS_HEADERS_nullify_hash(struct bean_CONTENTS_HEADERS_s *bean);

gint64 CONTENTS_HEADERS_get_size(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_size(struct bean_CONTENTS_HEADERS_s *bean, gint64 v);

gint64 CONTENTS_HEADERS_get_ctime(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_ctime(struct bean_CONTENTS_HEADERS_s *bean, gint64 v);

gint64 CONTENTS_HEADERS_get_mtime(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_mtime(struct bean_CONTENTS_HEADERS_s *bean, gint64 v);

GString * CONTENTS_HEADERS_get_mime_type(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_mime_type(struct bean_CONTENTS_HEADERS_s *bean, GString * v);
void CONTENTS_HEADERS_set2_mime_type(struct bean_CONTENTS_HEADERS_s *bean, const gchar *v);

GString * CONTENTS_HEADERS_get_chunk_method(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_chunk_method(struct bean_CONTENTS_HEADERS_s *bean, GString * v);
void CONTENTS_HEADERS_set2_chunk_method(struct bean_CONTENTS_HEADERS_s *bean, const gchar *v);

GString * CONTENTS_HEADERS_get_policy(struct bean_CONTENTS_HEADERS_s *bean);
void CONTENTS_HEADERS_set_policy(struct bean_CONTENTS_HEADERS_s *bean, GString * v);
void CONTENTS_HEADERS_set2_policy(struct bean_CONTENTS_HEADERS_s *bean, const gchar *v);
void CONTENTS_HEADERS_nullify_policy(struct bean_CONTENTS_HEADERS_s *bean);


/* Getters and Setters for CHUNKS */

GString * CHUNKS_get_id(struct bean_CHUNKS_s *bean);
void CHUNKS_set_id(struct bean_CHUNKS_s *bean, GString * v);
void CHUNKS_set2_id(struct bean_CHUNKS_s *bean, const gchar *v);

GByteArray * CHUNKS_get_content(struct bean_CHUNKS_s *bean);
void CHUNKS_set_content(struct bean_CHUNKS_s *bean, GByteArray * v);
void CHUNKS_set2_content(struct bean_CHUNKS_s *bean, const guint8 *v, gsize vlen);

GString * CHUNKS_get_position(struct bean_CHUNKS_s *bean);
void CHUNKS_set_position(struct bean_CHUNKS_s *bean, GString * v);
void CHUNKS_set2_position(struct bean_CHUNKS_s *bean, const gchar *v);

GByteArray * CHUNKS_get_hash(struct bean_CHUNKS_s *bean);
void CHUNKS_set_hash(struct bean_CHUNKS_s *bean, GByteArray * v);
void CHUNKS_set2_hash(struct bean_CHUNKS_s *bean, const guint8 *v, gsize vlen);

gint64 CHUNKS_get_size(struct bean_CHUNKS_s *bean);
void CHUNKS_set_size(struct bean_CHUNKS_s *bean, gint64 v);

gint64 CHUNKS_get_ctime(struct bean_CHUNKS_s *bean);
void CHUNKS_set_ctime(struct bean_CHUNKS_s *bean, gint64 v);


/* Getters and Setters for PROPERTIES */

GString * PROPERTIES_get_alias(struct bean_PROPERTIES_s *bean);
void PROPERTIES_set_alias(struct bean_PROPERTIES_s *bean, GString * v);
void PROPERTIES_set2_alias(struct bean_PROPERTIES_s *bean, const gchar *v);

gint64 PROPERTIES_get_version(struct bean_PROPERTIES_s *bean);
void PROPERTIES_set_version(struct bean_PROPERTIES_s *bean, gint64 v);

GString * PROPERTIES_get_key(struct bean_PROPERTIES_s *bean);
void PROPERTIES_set_key(struct bean_PROPERTIES_s *bean, GString * v);
void PROPERTIES_set2_key(struct bean_PROPERTIES_s *bean, const gchar *v);

GByteArray * PROPERTIES_get_value(struct bean_PROPERTIES_s *bean);
void PROPERTIES_set_value(struct bean_PROPERTIES_s *bean, GByteArray * v);
void PROPERTIES_set2_value(struct bean_PROPERTIES_s *bean, const guint8 *v, gsize vlen);


/* Getters and Setters for ALIASES */

GString * ALIASES_get_alias(struct bean_ALIASES_s *bean);
void ALIASES_set_alias(struct bean_ALIASES_s *bean, GString * v);
void ALIASES_set2_alias(struct bean_ALIASES_s *bean, const gchar *v);

gint64 ALIASES_get_version(struct bean_ALIASES_s *bean);
void ALIASES_set_version(struct bean_ALIASES_s *bean, gint64 v);

GByteArray * ALIASES_get_content(struct bean_ALIASES_s *bean);
void ALIASES_set_content(struct bean_ALIASES_s *bean, GByteArray * v);
void ALIASES_set2_content(struct bean_ALIASES_s *bean, const guint8 *v, gsize vlen);

gboolean ALIASES_get_deleted(struct bean_ALIASES_s *bean);
void ALIASES_set_deleted(struct bean_ALIASES_s *bean, gboolean v);

gint64 ALIASES_get_ctime(struct bean_ALIASES_s *bean);
void ALIASES_set_ctime(struct bean_ALIASES_s *bean, gint64 v);

gint64 ALIASES_get_mtime(struct bean_ALIASES_s *bean);
void ALIASES_set_mtime(struct bean_ALIASES_s *bean, gint64 v);


#endif /* GENERATED_H */
