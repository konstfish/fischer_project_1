#include "RequestCoordinator.h"

using namespace std;

void RequestCoordinator::print_queue(){
    cout << "Coord: Current Queue Size: " << node_queue.size() << endl;
    cout << "Coord: Current Node: " << node_queue.front() << endl;
    cout << "Coord: Last Node: " << node_queue.back() << endl;
}

void RequestCoordinator::message_req(int id){
    unique_lock<mutex> ul{mtx};

    node_queue.push(id);

    // print_queue();

    while(id != node_queue.front()){
        spot_taken.wait(ul);
    }

    fmt::print(fg(fmt::color::light_salmon) | fmt::emphasis::italic,
        "Coord : OK to Node {}\n", id);
    
}

void RequestCoordinator::message_rel(){
    unique_lock<mutex> ul{mtx};

    node_queue.pop();

    spot_taken.notify_one();
}

void RequestCoordinator::operator()(){
    httplib::Server svr;

    svr.Get("/req", [](const Request& req, Response& res) {
        if (req.has_param("id")) {
            auto id = req.get_param_value("key");

            // TODO

        }else{
            res.set_content("Invalid Request")
        }
        res.set_content("OK", "text/plain");
    });


    svr.listen("127.0.0.1", 5001);


}