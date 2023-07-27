#pragma once 

#include "../Runtime/Reference.hpp"
#include "../Core/ArrayView.hpp"

namespace YAWN {
    struct PipelineBinding {

    };

    class GraphicsPipeline : public Reference {
        YAWN_OBJECT(GraphicsPipeline, Reference);

    public:
        virtual ~GraphicsPipeline() = default;

    protected:
        GraphicsPipeline();
    };
}
