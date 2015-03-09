#include "segments.hpp"

Segments::Segments(uint32_t plate_area)
{
    _area = plate_area;
    segment = new uint32_t[plate_area];
    memset(segment, 255, plate_area * sizeof(uint32_t));
}

Segments::~Segments()
{   
    delete[] segment;
    segment = NULL;
    _area = 0;
    for (int i=0; i<seg_data.length(); i++){
        delete seg_data[i];
    }
}

uint32_t Segments::area()
{
    return _area;
}

void Segments::reset()
{
    memset(segment, -1, sizeof(uint32_t) * _area);
    seg_data.clear();
}

void Segments::reassign(uint32_t newarea, uint32_t* tmps)
{
    delete[] segment;
    _area = newarea;
    segment = tmps;
}

void Segments::shift(uint32_t d_lft, uint32_t d_top)
{
    for (uint32_t s = 0; s < seg_data.size(); ++s)
    {
        seg_data[s]->shift(d_lft, d_top);
    }
}

uint32_t Segments::size() const
{
    return seg_data.size();
}

const ISegmentData& Segments::operator[](uint32_t index) const
{
    return *seg_data[index];
}

ISegmentData& Segments::operator[](uint32_t index)
{
    return *seg_data[index];
}

void Segments::add(ISegmentData* data){
    seg_data.push_back(data);
}

const ContinentId& Segments::id(uint32_t index) const {
    if (index>=_area) {
        throw runtime_error("unvalid index");
    }
    return segment[index];
}

ContinentId& Segments::id(uint32_t index) {
    if (index>=_area) {
        throw runtime_error("unvalid index");
    }
    return segment[index];
}

void Segments::setId(uint32_t index, ContinentId id) const {
    if (index>=_area) {
        throw runtime_error("unvalid index");
    }
    segment[index] = id;
}

ContinentId Segments::getContinentAt(int x, int y) const
{
    if (_bounds == NULL) throw runtime_error("(Segments::getContinentAt) bounds not set");
    if (_segmentCreator == NULL) throw runtime_error("(Segments::getContinentAt) segmentCreator not set");
    uint32_t lx = x, ly = y;
    uint32_t index = _bounds->getValidMapIndex(&lx, &ly);
    ContinentId seg = id(index);

    if (seg >= size()) {
        // in this case, we consider as const this call because we calculate
        // something that we would calculate anyway, so the segments are
        // a sort of cache
        //seg = const_cast<plate*>(this)->createSegment(lx, ly);
        seg = _segmentCreator->createSegment(lx, ly);
    }

    if (seg >= size())
    {
        throw invalid_argument("Could not create segment");
    }
    return seg;  
}
