#include "Coordinator.h"

using namespace std;

void Coordinator::print_queue(){
    cout << "Coord: Current Queue Size: " << node_queue.size() << endl;
    if(node_queue.size() >= 2){
        cout << "Coord: Current Node: " << node_queue.front() << endl;
        cout << "Coord: Last Node: " << node_queue.back() << endl;
    }
}

void Coordinator::message_req(int id){
    unique_lock<mutex> ul{mtx};

    node_queue.push(id);

    // print_queue();

    while(id != node_queue.front()){
        spot_taken.wait_for(ul, 1s);
    }

    collect_stats();

    fmt::print(fg(fmt::color::light_salmon) | fmt::emphasis::italic,
        "Coord : OK to Node {}\n", id);
}

void Coordinator::message_rel(){
    unique_lock<mutex> ul{mtx};

    node_queue.pop();

    spot_taken.notify_one();
}


// only used to dected Node outages
void Coordinator::operator()(){
    int cnt{0};
    int timeout{8};
    int cur_id{-1};

    while(true){
        if(node_queue.size() > 0){
            this_thread::sleep_for(1s);
            if(node_queue.front() == cur_id){
                cnt += 1;
            }else{
                cur_id = node_queue.front();
                cnt = 0;
            }

            if(cnt == timeout){
                st.failed_nodes += 1;
                fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                    "Coord : Node {} didn't respond within {} seconds, removing from Queue\n", cur_id, timeout);
                node_queue.pop();
                st.recoveries += 1;
            }
        }
    }
}

void Coordinator::collect_stats(){
    st.admitted_nodes += 1;
    if(node_queue.size() > st.max_queue_size){
        st.max_queue_size = node_queue.size();
    }
}

void Coordinator::output_stat_table(){
    auto duration = chrono::duration_cast<chrono::seconds> (std::chrono::system_clock::now() - start);

    int tmp = duration.count();

    if(tmp > 3){
        fmt::print(fmt::emphasis::bold,
            "Final Stats:\n");

        tabulate::Table stat_table;

        size_t headers = 4;

        stat_table.add_row({"No. of Admitted Nodes", 
                            "Maximum Queue Size", 
                            "Failed Nodes/Recoveries",
                            "Total Time Spent Running"});

        stat_table.add_row({to_string(st.admitted_nodes), 
                            to_string(st.max_queue_size), 
                            to_string(st.failed_nodes) + '/' + to_string(st.recoveries),
                            to_string(tmp) + 's'});

        for (size_t i = 0; i < headers; ++i) {
            stat_table[0][i].format()
            .font_color(tabulate::Color::yellow)
            .font_align(tabulate::FontAlign::center)
            .font_style({tabulate::FontStyle::bold});
        } 

        std::cout << stat_table << std::endl;
    }
}