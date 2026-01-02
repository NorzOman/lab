
#include <crow/app.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <crow/json.h>
#include <crow/mustache.h>
#include <iostream>
#include <crow.h>

#include "studentHandler/student.h"
#include "middlware/middleware.h"

int main(){
    // -- create the classroom object --
    std::cout << "[ *] Creating clasroom object" << std::endl;

    classroom c;

    crow::App<labMiddleware> app;

    crow::mustache::set_base("templates");

    // -- templates --
    CROW_ROUTE(app,"/")([](){
        crow::mustache::context ctx;
        return crow::mustache::load("index.html").render(ctx);
    });

    CROW_ROUTE(app,"/style.css")([](){
        crow::mustache::context ctx;
        return crow::mustache::load("style.css").render(ctx);
    });

    // -- creates a empty classroom --
    // {
    //     "classFacutly": "Vivek Sir",
    //     "className": "CSE-ICB"
    // }

    CROW_ROUTE(app,"/api/add-clasroom")([&c](const crow::request& req){
        auto body = crow::json::load(req.body);
        c.classFaculty = body["classFacutly"].s();
        c.className = body["className"].s();
        return crow::response(200);
    });


    // --- Route to take the intake of all the students
    // [
    //     {
    //         "studentName": "Alice",
    //         "studentId": "S001",
    //         "optedSubjects": ["Math", "Physics"]
    //     },
    //     {
    //         "studentName": "Bob",
    //         "studentId": "S002",
    //         "optedSubjects": ["Chemistry", "Biology"]
    //     }
    // ]

    CROW_ROUTE(app,"/api/add-students")([&c](const crow::request& req){
        auto body = crow::json::load(req.body);
        // json array of strings
        for(auto& mates : body){
            student s;
            s.studentName = mates["studentName"].s();
            s.studentId = mates["studentId"].s();
            for(auto sub : s["optedSubjects"]){
                subject sbt;
                sbt.subName = sub.s();
                s.optedSubjects.push_back(sbt);
            }
            c.batch.push_back(s);
        }
        return crow::response(200);
    });


    CROW_ROUTE(app, "/api/post-student-marks")([](const crow::request& req){
        auto body = crow::json::load(req.body);

    });

    app.port(5000).run()
}
