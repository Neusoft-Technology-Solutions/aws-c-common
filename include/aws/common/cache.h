#ifndef AWS_COMMON_CACHE_H
#define AWS_COMMON_CACHE_H
/*
 * Copyright 2010-2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/common/linked_hash_table.h>

struct aws_cache;

struct aws_cache_vtable {
    void (*clean_up)(struct aws_cache *cache);
    int (*find)(struct aws_cache *cache, const void *key, void **p_value);
    int (*put)(struct aws_cache *cache, const void *key, void *p_value);
    int (*remove)(struct aws_cache *cache, const void *key);
    void (*clear)(struct aws_cache *cache);
    size_t (*get_element_count)(const struct aws_cache *cache);

    /* LRU-only functions */
    void *(*use_lru_element)(struct aws_cache *cache);
    void *(*get_mru_element)(const struct aws_cache *cache);
};

/**
 * Base stucture for caches using the linked hash table implementation.
 */
struct aws_cache {
    struct aws_allocator *allocator;
    const struct aws_cache_vtable *vtable;
    struct aws_linked_hash_table table;
    size_t max_items;
};

int aws_cache_base_find(struct aws_cache *cache, const void *key, void **p_value);
int aws_cache_base_remove(struct aws_cache *cache, const void *key);
void aws_cache_base_clear(struct aws_cache *cache);
size_t aws_cache_base_get_element_count(const struct aws_cache *cache);

AWS_EXTERN_C_BEGIN
/**
 * Cleans up the cache. Elements in the cache will be evicted and cleanup
 * callbacks will be invoked.
 */
AWS_COMMON_API
void aws_cache_clean_up(struct aws_cache *cache);

/**
 * Finds element in the cache by key. If found, *p_value will hold the stored value, and AWS_OP_SUCCESS will be
 * returned. If not found, AWS_OP_SUCCESS will be returned and *p_value will be NULL.
 *
 * If any errors occur AWS_OP_ERR will be returned.
 */
AWS_COMMON_API
int aws_cache_find(struct aws_cache *cache, const void *key, void **p_value);

/**
 * Puts `p_value` at `key`. If an element is already stored at `key` it will be replaced. If the cache is already full,
 * based on the implementation, item will be removed.
 */
AWS_COMMON_API
int aws_cache_put(struct aws_cache *cache, const void *key, void *p_value);

/**
 * Removes item at `key` from the cache.
 */
AWS_COMMON_API
int aws_cache_remove(struct aws_cache *cache, const void *key);

/**
 * Clears all items from the cache.
 */
AWS_COMMON_API
void aws_cache_clear(struct aws_cache *cache);

/**
 * Returns the number of elements in the cache.
 */
AWS_COMMON_API
size_t aws_cache_get_element_count(const struct aws_cache *cache);

AWS_EXTERN_C_END

#endif /* AWS_COMMON_FIFO_CACHE_H */
