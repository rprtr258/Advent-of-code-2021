main :: () -> () {
    pipe (stdin) {
        iterate(readline),
        map([s] -> s.split(' ')),
        map*(id, parse::int),
        reduce([[dir, value], [depth, distance]] -> match (dir) {
            "up" => (depth - value, distance),
            "down" => (depth + value, distance),
            "forward" => (depth, distance + value),
        }, [0, 0]),
        prod,
        print,
    }
}

(require '[clojure.string :refer [split]])

(->> *in*
    java.io.BufferedReader.
    line-seq
    (map (fn [s] (split s #" ")))
    (map (fn [[dir value]] [(keyword dir) (Integer/parseInt value)]))
    (reduce (fn [[depth, distance] [dir, value]]
        ({:up [(- depth value) distance]
        :down [(+ depth value) distance]
        :forward [depth (+ distance value)]} dir))
        [0, 0])
    ((fn [[depth distance]] (* depth distance)))
    print)
