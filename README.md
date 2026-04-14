# C++ Raycasting & Rendering Engine

This project implements a raycasting-based rendering engine in C++, designed using modular architecture and object-oriented principles.

## Features

* Raycasting system implemented through a Viewport component
* Scene management with dynamic initialization and rendering
* Custom pixel buffer (ColorBuffer) with manual memory management
* Line rasterization using Bresenham’s algorithm
* Ray traversal using point generators
* Detection of object intersections and distance calculation
* Serialization of pixel data for image output

## Architecture

* Scene: manages the environment and rendering pipeline
* Viewport: responsible for raycasting and field-of-view handling
* ColorBuffer: handles pixel storage and rendering operations
* Line & PointGenerator: used for geometric traversal and drawing

## Technologies

* C++
* Object-Oriented Programming (OOP)
* Low-level memory management (dynamic allocation)
* Geometry and rendering algorithms

## How to Build

g++ *.cpp -o app

## How to Run

./app

## Description

The system simulates a virtual scene and renders it using raycasting techniques, similar to early 3D rendering engines.
