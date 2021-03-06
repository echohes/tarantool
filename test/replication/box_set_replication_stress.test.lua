test_run = require('test_run').new()
SERVERS = {'master_quorum1', 'master_quorum2'}

-- Deploy a cluster.
test_run:create_cluster(SERVERS)
test_run:wait_fullmesh(SERVERS)

test_run:cmd("switch master_quorum1")
repl = box.cfg.replication
for i = 1, 1000 do              \
    box.cfg{replication = ""}   \
    box.cfg{replication = repl} \
end
test_run:cmd("switch default")

-- Cleanup.
test_run:drop_cluster(SERVERS)
