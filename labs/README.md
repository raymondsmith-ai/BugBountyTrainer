# BugBountyTrainer Docker Lab



Requires Docker Desktop running Linux containers and Docker Compose.

Run commands from the BugBountyTrainer repository root.



## Start

```powershell

docker compose -f ./labs/compose.yaml up -d --build

```



Open http://127.0.0.1:8085



## Health check

```powershell

curl.exe --noproxy "*" http://127.0.0.1:8085/health

```



Expected response: ok



## Stop

```powershell

docker compose -f ./labs/compose.yaml stop

```



## Reset

```powershell

docker compose -f ./labs/compose.yaml restart sql-lab

```



Restarting recreates the in-memory database with three fictional records.

Open the home page to clear the browser form.



## Troubleshooting

```powershell

docker compose -f ./labs/compose.yaml ps -a

docker compose -f ./labs/compose.yaml logs --tail 40

```



## Verified exercises

- Normal search: Training Notebook returns one product priced at 12.

- Vulnerable search: ' OR 1=1 -- returns all three fictional products.

- Parameterized search: the same input returns no matching products.

- Health check and normal search work after restarting.



## Network

The published website binds to 127.0.0.1:8085.

The container's bridge network permits outbound access.

Keep the vulnerable lab local and use fictional data.



Burp Suite, Metasploit, and trainer XP integration remain future work.


