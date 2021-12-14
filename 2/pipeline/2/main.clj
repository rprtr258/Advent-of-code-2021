main :: () -> () {
    pipe (stdin) {
        iterate(readline),
        map([s] -> s.split(' ')),
        map*(id, parse::int),
        reduce([[depth, distance aim], [dir, value]] -> match (dir) {
            "up" => (depth, distance, aim - value),
            "down" => (depth, distance, aim + value),
            "forward" => (depth + aim * value, distance + value, aim),
        }, [0, 0, 0]),
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
    (reduce (fn [[depth, distance, aim] [dir, value]]
        ({:up [depth distance (- aim value)]
        :down [depth distance (+ aim value)]
        :forward [(+ depth (* aim value)) (+ distance value) aim]} dir))
        [0, 0, 0])
    ((fn [[depth distance]] (* depth distance)))
    print)
