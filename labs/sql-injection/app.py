import html
import sqlite3
from http.server import BaseHTTPRequestHandler, HTTPServer
from urllib.parse import parse_qs, urlparse

db = sqlite3.connect(":memory:")
db.executescript("""
CREATE TABLE products (
    id INTEGER PRIMARY KEY,
    name TEXT,
    price INTEGER,
    published INTEGER
);
INSERT INTO products VALUES
    (1, 'Training Notebook', 12, 1),
    (2, 'Practice Keyboard', 35, 1),
    (3, 'BBT Hidden Training Record', 0, 0);
""")

PAGE = """
<!doctype html>
<html lang="en">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>BugBountyTrainer SQL Lab</title>
<style>
body {{font-family:Arial,sans-serif;max-width:850px;
margin:40px auto;padding:20px;background:#111827;color:#e5e7eb}}
section {{background:#1f2937;padding:24px;border-radius:12px}}
input,select,button {{padding:10px;margin:6px 0;max-width:100%}}
pre {{white-space:pre-wrap;overflow-wrap:anywhere;background:#111827;
padding:16px}}
table {{width:100%;border-collapse:collapse}}
td,th {{text-align:left;padding:10px;border-bottom:1px solid #475569}}
a {{color:#93c5fd}}
</style>
</head>
<body>
<h1>BugBountyTrainer: SQL Injection Lab</h1>
<p>Local practice environment. All records are fictional.</p>
<section>
<h2>Product Search</h2>
<p>Search by exact product name. Only published products should appear.</p>
<form action="/search" method="get">
<label>Search mode:
<select name="mode">
<option value="vulnerable" {vselected}>Vulnerable query</option>
<option value="safe" {sselected}>Parameterized query</option>
</select></label><br>
<label>Product name:
<input name="q" value="{query}" placeholder="Training Notebook">
</label>
<button type="submit">Search</button>
</form>
{result}
</section>
<




h2>Your objectives</h2>
<ol>
<li>Search for Training Notebook and inspect the normal response.</li>
<li>Use Burp Suite to inspect the GET /search request.</li>
<li>Investigate how input changes the vulnerable SQL query.</li>
<li>Try to reveal the hidden training record.</li>
<li>Repeat the same input in parameterized mode and compare results.</li>
</ol>
<p>The query display below is teaching feedback.
External lab completion and XP are not connected yet.</p>
<p><a href="/">Return to start</a></p>
</body>
<











/html>
"""

class Handler(BaseHTTPRequestHandler):
    def do_GET(self):
        request = urlparse(self.path)
        if request.path == "/health":
            self.send_response(200)
            self.end_headers()
            self.wfile.write(b"ok")
 









            return

        if request.path not in ("/", "/search"):
            self.send_error(404)
            return

        values = parse_qs(request.query, keep_blank_values=True)
        query = values.get("q", [""])[0]
 







        mode = values.get("mode", ["vulnerable"])[0]
        if mode not in ("vulnerable", "safe"):
            self.send_error(400, "Unknown search mode")
            return
        if len(query) > 500:
            self.send_error(400, "Search input is too long")
 





            return

        result = ""
        if request.path == "/search":
            try:
                if mode == "safe":
 





                    sql = (
                        "SELECT id, name, price FROM products "
                        "WHERE name = ? AND published = 1"
                    )
                    rows = db.execute(sql, (query,)).fetchall()
 




                    details = sql + "\nBound value: " + repr(query)
                else:
                    # Intentionally unsafe: local training exercise only.
                    sql = (
 



                        "SELECT id, name, price FROM products "
                        "WHERE name = '" + query + "' AND published = 1"
                    )
                    details = sql
 



                    rows = db.execute(sql).fetchall()

                result = "<h3>Results</h3>"
                if rows:
 



                    result += "<table><tr><th>ID</th><th>Name</th><th>Price</th></tr>"
                    for row in rows:
                        result += "<tr>" + "".join(
 


                            "<td>" + html.escape(str(value)) + "</td>"
                            for value in row
                        ) + "</tr>"
 


                    result += "</table>"
                else:
                    result += "<p>No matching products.</p>"




                if any(row[0] == 3 for row in rows):
                    result += (
 


                        "<p><strong>Objective reached:</strong> "
                        "the hidden fictional record was returned.</p>"
                    )
 


                result += "<h3>Query details</h3><pre>"
                result += html.escape(details) + "</pre>"
            except sqlite3.Error as error:
 


                result = "<h3>SQL error</h3><pre>"
                result += html.escape(str(error)) + "</pre>"



        page = PAGE.format(
 

            query=html.escape(query, quote=True),
            vselected="selected" if mode == "vulnerable" else "",
 

            sselected="selected" if mode == "safe" else "",
            result=result,
 

        ).encode("utf-8")

 

        self.send_response(200)
        self.send_header("Content-Type", "text/html; charset=utf-8")
 

        self.send_header("Content-Length", str(len(page)))
        self.send_header("Cache-Control", "no-store")
 

        self.end_headers()
        self.wfile.write(page)



print("BBT SQL training app listening on port 8000", flush=True)
HTTPServer(("0.0.0.0", 8000), Handler).serve_forever()
