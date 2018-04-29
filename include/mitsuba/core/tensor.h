#pragma once

#include <mitsuba/core/mmap.h>
#include <mitsuba/core/struct.h>
#include <unordered_map>

NAMESPACE_BEGIN(mitsuba)

/**
 * \brief Simple exchange format for tensor data of arbitrary rank and size
 *
 * This class provides convenient memory-mapped read-only access to tensor
 * data, usually exported from NumPy.
 */
class MTS_EXPORT_CORE TensorFile : public MemoryMappedFile {
public:
    /// Information about the specified field
    struct Field {
        Struct::EType dtype;
        size_t offset;
        std::vector<size_t> shape;
        const void *data;
    };

    /// Map the specified file into memory
    TensorFile(const fs::path &filename);

    /// Does the file contain a field of the specified name?
    bool has_field(const std::string &name) const;

    /// Return a data structure with information about the specified field
    const Field &field(const std::string &name) const;

    /// Return a human-readable summary
    std::string to_string() const override;

    MTS_DECLARE_CLASS()

protected:
    /// Destructor
    ~TensorFile();

private:
    std::unordered_map<std::string, Field> m_fields;
};

NAMESPACE_END(mitsuba)
