# Quick start
After cloning this repository, run <pre>make -f Autofile</pre> to update the auto files.

# Building
To build the project, run <pre>make</pre>
To clean the project, run <pre>make clean</pre>

# Auto files
Auto files are files that have each been generated with a corresponding shell script.
## Update auto files
To update the auto files, run <pre>make -f Autofile</pre>
Make sure the auto files are up to date before building the project.
## Clean auto files
To clean the auto files, run <pre>make -f Autofile clean</pre>

# Copy library
To copy the content of a built library (as well as the libraries it depends on) use <pre>bash copylib.sh</pre>
For more information, run <pre>bash copylib.sh --help</pre>
