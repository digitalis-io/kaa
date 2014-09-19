/*
 * Copyright 2014 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SCHEMAPERSISTENCEMANAGER_HPP_
#define SCHEMAPERSISTENCEMANAGER_HPP_

#include "kaa/schema/storage/ISchemaPersistenceManager.hpp"
#include "kaa/schema/ISchemaProcessor.hpp"
#include <boost/thread/mutex.hpp>

namespace kaa {


/**
 * \class SchemaPersistenceManager
 *
 * This class is responsible for persistence of data schema invoking
 * user-defined \c ISchemaStorage routines.
 *
 * Receives data schema updates from \c SchemaProcessor.
 *
 */
class SchemaPersistenceManager : public ISchemaPersistenceManager {
public:
    SchemaPersistenceManager()
        : storage_(NULL)
        , processor_(NULL)
        , ignoreSchemaUpdate_(false)
    {}

    /**
     * \c ISchemaPersistenceManager implementation
     */
    void setSchemaStorage(ISchemaStorage *storage);

    /**
     * \c ISchemaUpdatesReceiver implementation
     */
    void onSchemaUpdated(boost::shared_ptr<avro::ValidSchema> schema);

    /**
     * Sets the schema processor (see \c ISchemaProcessor)
     * which will handle restored data schema on start-up.
     *
     * @param processor Schema load handler.
     */
    void setSchemaProcessor(ISchemaProcessor *processor);
private:
    typedef boost::mutex                    mutex_type;
    typedef boost::unique_lock<mutex_type>  lock_type;

    void readStoredSchema();

    mutex_type          schemaGuard_;
    mutex_type          schemaPersistenceGuard_;

    ISchemaStorage *    storage_;
    ISchemaProcessor *  processor_;
    bool                ignoreSchemaUpdate_;
};

}  // namespace kaa


#endif /* SCHEMAPErsistenCEMANAGER_HPP_ */