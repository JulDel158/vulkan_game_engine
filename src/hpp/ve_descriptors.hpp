#pragma once

#include "ve_device.hpp"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace ve {

    class ve_descriptor_set_layout {
    public:
        class Builder {
        public:
            Builder(ve_device& lveDevice) : veDevice{ lveDevice } {}

            Builder& addBinding(
                uint32_t binding,
                VkDescriptorType descriptorType,
                VkShaderStageFlags stageFlags,
                uint32_t count = 1);
            std::unique_ptr<ve_descriptor_set_layout> build() const;

        private:
            ve_device& veDevice;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };

        ve_descriptor_set_layout(
            ve_device& lveDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
        ~ve_descriptor_set_layout();
        ve_descriptor_set_layout(const ve_descriptor_set_layout&) = delete;
        ve_descriptor_set_layout& operator=(const ve_descriptor_set_layout&) = delete;

        VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

    private:
        ve_device& veDevice;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

        friend class ve_descriptor_writer;
    };

    class ve_descriptor_pool {
    public:
        class Builder {
        public:
            Builder(ve_device& lveDevice) : veDevice{ lveDevice } {}

            Builder& addPoolSize(VkDescriptorType descriptorType, uint32_t count);
            Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
            Builder& setMaxSets(uint32_t count);
            std::unique_ptr<ve_descriptor_pool> build() const;

        private:
            ve_device& veDevice;
            std::vector<VkDescriptorPoolSize> poolSizes{};
            uint32_t maxSets = 1000;
            VkDescriptorPoolCreateFlags poolFlags = 0;
        };

        ve_descriptor_pool(
            ve_device& lveDevice,
            uint32_t maxSets,
            VkDescriptorPoolCreateFlags poolFlags,
            const std::vector<VkDescriptorPoolSize>& poolSizes);
        ~ve_descriptor_pool();
        ve_descriptor_pool(const ve_descriptor_pool&) = delete;
        ve_descriptor_pool& operator=(const ve_descriptor_pool&) = delete;

        bool allocateDescriptor(
            const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const;

        void freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;

        void resetPool();

    private:
        ve_device& veDevice;
        VkDescriptorPool descriptorPool;

        friend class ve_descriptor_writer;
    };

    class ve_descriptor_writer {
    public:
        ve_descriptor_writer(ve_descriptor_set_layout& setLayout, ve_descriptor_pool& pool);

        ve_descriptor_writer& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);
        ve_descriptor_writer& writeImage(uint32_t binding, VkDescriptorImageInfo* imageInfo);

        bool build(VkDescriptorSet& set);
        void overwrite(VkDescriptorSet& set);

    private:
        ve_descriptor_set_layout& setLayout;
        ve_descriptor_pool& pool;
        std::vector<VkWriteDescriptorSet> writes;
    };

}  // namespace ve

