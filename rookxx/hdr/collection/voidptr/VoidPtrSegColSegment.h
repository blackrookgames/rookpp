#include <cstddef>
#include <cstdint>

#ifndef rookxx_collection_voidptr_VoidPtrSegColSegment_h
#define rookxx_collection_voidptr_VoidPtrSegColSegment_h

namespace rookxx::collection::voidptr
{
    /// @brief INTERAL USE ONLY\
    /// @brief Represents a segment within a segmented collection
    class VoidPtrSegColSegment
    {
        #pragma region init

        /// @brief Constructor for VoidPtrSegColSegment
        public: VoidPtrSegColSegment();

        /// @brief Copy constructor for VoidPtrSegColSegment
        /// @param src Source
        public: VoidPtrSegColSegment(const VoidPtrSegColSegment& src);

        /// @brief Move constructor for VoidPtrSegColSegment
        /// @param src Source
        public: VoidPtrSegColSegment(VoidPtrSegColSegment&& src);

        /// @brief Destructor for VoidPtrSegColSegment
        public: ~VoidPtrSegColSegment();

        #pragma endregion

        #pragma region assignment

        /// @brief Copy assignment for VoidPtrSegColSegment
        /// @param src Source
        /// @return Current instance of VoidPtrSegColSegment
        public: VoidPtrSegColSegment& operator=(const VoidPtrSegColSegment& src);

        /// @brief Move assignment for VoidPtrSegColSegment
        /// @param src Source
        /// @return Current instance of VoidPtrSegColSegment
        public: VoidPtrSegColSegment& operator=(VoidPtrSegColSegment&& src);

        #pragma endregion
        
        #pragma region fields

        private: void* f_Data;
        private: VoidPtrSegColSegment* f_Next;

        #pragma endregion

        #pragma region properties
        
        /// @brief Pointer to data 
        public: void* data();
        /// @brief Pointer to data 
        public: const void* data() const;
        /// @brief Pointer to data 
        public: void data(void* value);

        /// @brief Pointer to next segment
        public: VoidPtrSegColSegment* next();
        /// @brief Pointer to next segment
        public: const VoidPtrSegColSegment* next() const;
        /// @brief Pointer to next segment
        public: void next(VoidPtrSegColSegment* value);

        #pragma endregion
    };
}

#endif