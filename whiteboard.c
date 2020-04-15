
struct election_t{
    Map tribe_id_to_name;
    AreaNode ballots;
};


struct areaNode_t{
     struct area_t area;
     struct areaNode_t next;

}

struct area_t{
    int area_id;
    char *area_name;
    Map ballot;
};