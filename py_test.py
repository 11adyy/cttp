import time
import requests
import subprocess


start_time = time.perf_counter()
print(requests.get("http://0.0.0.0:5000/api/moderators").text)
insert_time = time.perf_counter() - start_time
print(f'[Time] {insert_time:.4f} sec.')

start_time = time.perf_counter()
print(subprocess.run("./test"))
insert_time = time.perf_counter() - start_time
print(f'[Time] {insert_time:.4f} sec.')